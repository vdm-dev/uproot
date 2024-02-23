#include "argparse.hpp"

#include <filesystem>
#include <StormLib.h>


namespace fs = std::filesystem;
typedef std::vector<std::string> stringlist;
typedef std::basic_string<TCHAR> tstring;

stringlist languages({
    "enUS", "enGB", "enTW", "zhTW", "esES",
    "ruRU", "koKR", "ptPT", "esMX", "itIT",
    "deDE", "frFR", "enCN", "zhCN", "ptBR"
});

stringlist baseFiles({
    "common.MPQ",
    "common-2.MPQ",
    "expansion.MPQ",
    "lichking.MPQ"
});

stringlist extraFiles({
    "locale",
    "speech",
    "expansion-locale",
    "lichking-locale",
    "expansion-speech",
    "lichking-speech",
    "patch"
});

HANDLE mpq = nullptr;


tstring pathToString(const fs::path& path)
{
#if defined(UNICODE) || defined(_UNICODE)
    return path.wstring();
#else
    return path.string();
#endif
}


bool filesAreEqual(const char* extractedName, const char* packedName)
{
    HANDLE extractedFile;
    if (!SFileOpenFileEx(nullptr, extractedName, SFILE_OPEN_LOCAL_FILE, &extractedFile))
        return false;

    HANDLE packedFile;
    if (!SFileOpenFileEx(mpq, packedName, 0, &packedFile))
    {
        SFileCloseFile(extractedFile);
        return false;
    }

    char extractedData[4096];
    DWORD extractedRead = 0;

    char packedData[4096];
    DWORD packedRead = 0;

    bool result = true;

    while (true)
    {
        SFileReadFile(extractedFile, extractedData, sizeof(extractedData), &extractedRead, nullptr);
        SFileReadFile(packedFile, packedData, sizeof(packedData), &packedRead, nullptr);
        if (extractedRead != packedRead)
        {
            result = false;
            break;
        }
        if (extractedRead == 0)
            break;

        if (memcmp(extractedData, packedData, extractedRead))
        {
            result = false;
            break;
        }
    }

    SFileCloseFile(packedFile);
    SFileCloseFile(extractedFile);
    return result;
}

int extract(const fs::path& output)
{
    SFILE_FIND_DATA data = { 0 };

    HANDLE search = SFileFindFirstFile(mpq, "*", &data, nullptr);
    if (!search)
    {
        std::cerr << "No files found inside MPQ";
        return ENOENT;
    }

    size_t total = 0;
    size_t updated = 0;
    size_t added = 0;
    size_t skipped = 0;
    size_t errors = 0;

    while (true)
    {
        fs::path outputFile = output / data.cFileName;
        fs::create_directories(outputFile.parent_path());
        if (fs::exists(outputFile))
        {
            if (fs::file_size(outputFile) != data.dwFileSize)
            {
                if (SFileExtractFile(mpq, data.cFileName, pathToString(outputFile).c_str(), 0))
                {
                    std::cout << "[*] " << outputFile << std::endl;
                    updated++;
                }
                else
                {
                    std::cout << "[!] " << outputFile << std::endl;
                    errors++;
                }
            }
            else if (filesAreEqual(outputFile.string().c_str(), data.cFileName))
            {
                std::cout << "[=] " << outputFile << std::endl;
                skipped++;
            }
            else
            {
                if (SFileExtractFile(mpq, data.cFileName, pathToString(outputFile).c_str(), 0))
                {
                    std::cout << "[*] " << outputFile << std::endl;
                    updated++;
                }
                else
                {
                    std::cout << "[!] " << outputFile << std::endl;
                    errors++;
                }
            }
        }
        else
        {
            if (SFileExtractFile(mpq, data.cFileName, pathToString(outputFile).c_str(), 0))
            {
                std::cout << "[+] " << outputFile << std::endl;
                added++;
            }
            else
            {
                std::cout << "[!] " << outputFile << std::endl;
                errors++;
            }
        }
        total++;

        if (!SFileFindNextFile(search, &data))
            break;
    }

    SFileFindClose(search);

    std::cout << "Added  : " << added << std::endl;
    std::cout << "Updated: " << updated << std::endl;
    std::cout << "Skipped: " << skipped << std::endl;
    std::cout << "Errors : " << errors << std::endl;
    std::cout << "Total  : " << total << std::endl;

    return 0;
}

void openExtraArchive(const fs::path& path, const std::string& fileNamePrefix)
{
    for (size_t i = 1; i < 20; ++i)
    {
        std::string fileName = fileNamePrefix;
        if (i > 1)
            fileName += "-" + std::to_string(i);

        fileName += ".MPQ";

        tstring mpqName = pathToString(path / fileName);
        if (!SFileOpenPatchArchive(mpq, mpqName.c_str(), nullptr, 0))
            return;
    }
}

int openArchives(const fs::path& input, const fs::path& output)
{
    std::string language;
    for (const auto& folderName : languages)
    {
        if (fs::is_directory(input / folderName))
        {
            language = folderName;
            break;
        }
    }
    if (language.empty())
    {
        std::cerr << "Unable to find the language folder";
        return ENOTDIR;
    }

    for (const auto& fileName : baseFiles)
    {
        tstring mpqName = pathToString(input / fileName);
        bool result;
        if (mpq)
        {
            result = SFileOpenPatchArchive(mpq, mpqName.c_str(), nullptr, 0);
        }
        else
        {
            result = SFileOpenArchive(mpqName.c_str(), 0, MPQ_FLAG_READ_ONLY, &mpq);
        }
        if (!result)
        {
            std::cerr << "Unable to find " << (input / fileName);
            return ENOENT;
        }
    }

    for (const auto& fileName : extraFiles)
    {
        openExtraArchive(input / language, fileName + "-" + language);
    }

    openExtraArchive(input / language, "patch");
    openExtraArchive(input, "patch");
    return 0;
}

int main(int argc, char* argv[])
{
    argparse::ArgumentParser program("uproot");

    program.add_argument("-o", "--output")
        .metavar("OUTPUT")
        .required()
        .help("set the output path");

    program.add_argument("input")
        .metavar("INPUT")
        .required()
        .help("the input path");

    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return 1;
    }

    auto input = fs::path(program.get<std::string>("input"));

    if (!fs::exists(input))
    {
        std::cerr << "The input path does not exist";
        return ENOENT;
    }

    if (!fs::is_directory(input))
    {
        std::cerr << "The input path is not a folder";
        return ENOTDIR;
    }

    if (!fs::is_regular_file(input / "common.MPQ"))
    {
        input /= "Data";
        if (!fs::is_regular_file(input / "common.MPQ"))
        {
            std::cerr << "Unable to find MPQ files in the input folder";
            return ENOENT;
        }
    }

    auto output = fs::path(program.get<std::string>("-o"));
    if (fs::exists(output) && !fs::is_directory(output))
    {
        std::cerr << "The output path is not a folder";
        return ENOTDIR;
    }

    int result = openArchives(input, output);
    if (result != 0)
        return result;

    return extract(output);
}