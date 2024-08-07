#include <bits/stdc++.h>
#include <filesystem>
#include <cerrno>

class Main{

private:
    std::filesystem::path income, outcome; //откуда куда конвертировать
    std::string extension, disc; //расширение и тип диска

    std::unordered_map<std::string, bool> audio_table, video_table, pic_table; //будут хранится расширения файлов 



    void INIT_TABLES() //таблица с форматами
    {
        audio_table = {{".3gp", 1}, {".aa", 1}, {".aac", 1}, {".aax", 1}, {".act", 1}, {".aiff", 1}, {".alac", 1}, {".amr", 1}, {".ape", 1}, {".au", 1}, {".awb", 1}, {".dss", 1}, {".dvf", 1}, {".flac", 1}, {".gsm", 1}, {".iklax", 1}, {".ivs", 1}, {".m4a", 1}, {".m4b", 1}, {".m4p", 1}, {".mmf", 1}, {".movpkg", 1}, {".mp3", 1}, {".mpc", 1}, {".msv", 1}, {".nmf", 1}, {".ogg", 1}, {".oga", 1}, {".mogg", 1}, {".opus", 1}, {".ra", 1}, {".rm", 1}, {".raw", 1}, {".rf64", 1}, {".sln", 1}, {".tta", 1}, {".voc", 1}, {".vox", 1}, {".wav", 1}, {".wma", 1}, {".wv", 1}, {".webm", 1}, {".8svx", 1}, {".cda", 1}};
        video_table = {{".webm", 1}, {".mkv", 1}, {".flv", 1}, {".vob", 1}, {".ogv", 1}, {".ogg", 1}, {".drc", 1}, {".gif", 1}, {".gifv", 1}, {".mng", 1}, {".avi", 1}, {".MTS", 1}, {".M2TS", 1}, {".M2TS", 1}, {".mov", 1}, {".qt", 1}, {".wmv", 1}, {".yuv", 1}, {".rm", 1}, {".rmvb", 1}, {".viv", 1}, {".asf", 1}, {".amv", 1}, {".mp4", 1}, {".m4p", 1}, {".m4v", 1}, {".mpg", 1}, {".mp2", 1}, {".mpeg", 1}, {".mpe", 1}, {".mpv", 1}, {".mpg", 1}, {".mpeg", 1}, {".m2v", 1}, {".m4v", 1}, {".svi", 1}, {".3gp", 1}, {".3g2", 1}, {".mxf", 1}, {".roq", 1}, {".nsv", 1}, {".flv", 1}, {".f4v", 1}, {".f4p", 1}, {".f4a", 1}, {".f4b", 1}};
        return;
    }




    std::string DISC_FORMAT() //дисковые форматы европы
    {
        if (video_table[extension])
        {
            if (disc == "svcd" || disc == "cd")
            {
                return " -target pal-svcd ";
            }
            else if (disc == "dvd")
            {
                return " -target pal-dvd ";
            }
            else
            {
                return " ";
            }
        }
        return " ";
    }




    std::string CREATE_COMMAND(std::string in_file, std::string out_file)
    {
        std::string command = "ffmpeg -i ";

        command += char(34);
        command += in_file;
        command += char(34);
        command += ' ';
        command += DISC_FORMAT(); //добавление дисковых форматов европы
        if (audio_table[extension]) //если аудио то добавить
        {
            command += " -acodec pcm_s16le -ar 44100 -map_metadata 0 ";
        }
        command += char(34);
        command += out_file;
        command += char(34);

        return command;
    }




    std::string CHANGE_EXTENSION_NAME(std::filesystem::path path) //изменение формата
    {
        path.replace_extension(extension);
        return path.filename();
    }




    bool CHECK(std::filesystem::path& path) //проверяет является ли путь к файлу/папке чем-то с таким же форматом, что и требуемый конечный
    {
        std::string extension_str = path.std::filesystem::path::extension();
        std::cout << audio_table[extension_str] << ' ' << audio_table[extension] << '\n';
        if (((audio_table[extension_str] & audio_table[extension]) || (video_table[extension_str] & video_table[extension]) || (pic_table[extension_str] & pic_table[extension])))
        {
            return true;
        }
        else
        {
            return false;
        }
    }




    void CHANGE_START() //проходится по папке с файлами и использует функции что есть
    {
        std::filesystem::directory_iterator it{income};

        while (it != std::filesystem::directory_iterator{})
        {
            std::filesystem::path path = *it++;
            //std::cout << path.std::filesystem::path::extension() << '\n';
            if (CHECK(path)) //проверка на то, что файл подходящего типа
            {
                std::string in_file = path; //начальный путь
                std::string out_file = outcome; 
                out_file += "/";
                out_file += CHANGE_EXTENSION_NAME(path); //изменение расширения, конечный путь
                std::string command = CREATE_COMMAND(in_file, out_file); //создание команды

                //command += " & ";
                std::cout << command << '\n';
                system(command.c_str());
            }
        }
        //system("time");
        return;
    }




    void MAKE_DIRECTORY()
    {
        std::filesystem::create_directories(outcome);
        return;
    }




    void INIT() //принимание всех данных (откуда, куда, расширение, диск)
    {
        std::string income_str, outcome_str, extension_str, disc_str;

        std::cout << "Income path: "; getline(std::cin, income_str);
        std::cout << "Outcome path: "; getline(std::cin, outcome_str);
        std::cout << "Extension (type with point '.'): "; getline(std::cin, extension_str);
        std::cout << "Disc-type (if you don't know, than type bluray): "; getline(std::cin, disc_str);

        income = income_str;
        outcome = outcome_str;
        extension = extension_str;
        disc = disc_str;
        return;
    }



public:
    void BEGIN() //начало начал
    {
        INIT_TABLES(); //заполнение таблиц с форматами
        INIT(); //приём данных
        MAKE_DIRECTORY(); //создать папки
        CHANGE_START(); //переконвертировать

        return;
    }
protected:

};