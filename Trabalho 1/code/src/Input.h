#ifndef STREAMZ_INPUT_H
#define STREAMZ_INPUT_H
#include <string>
#include <iostream>
#include <sstream>

#define MAX_NAME_LENGHT 20
#define MAX_NICKNAME_LENGHT 10
#define MAX_TITLE_LENGHT 20

namespace input{
    /**
     * Get a string from cin
     * @return string
     */
    std::string getRaw();

    /**
     * Remove leading/trailing whitespace from string,
     * and reduces multiple consecutive whitespaces into a single one
     * e.g "example      string" => "example string"
     * @param str - String to be changed
     */
    void trimString(std::string &str);

    /**
     * Convert a string to a var of type T
     * @tparam T - Type with defined >> operator
     * @param str - String to be read
     * @param var - Output after reading
     * @return true if operation was successful
     */
    template <typename T>
    bool strToVar(const std::string &str, T &var){
        std::istringstream ss{str};
        ss >> var;
        if(ss.fail() || !ss.eof()){
            return false;
        }
        return true;
    }

    /**
     * Get a var of type T from cin
     * @tparam T - Type with defined >> operator
     * @param var - Output
     * @return true if operation was successful
     */
    template <typename T>
    bool get(T &var){
        std::string str = getRaw();
        if(str.empty()){
            return false;
        }
        return strToVar(str, var);
    }

    /**
     * Wait for user to press enter
     */
    void waitEnter();

    /**
     * Check if nickname is valid
     * @param nickname
     * @return true if valid
     */
    bool validateNickname(const std::string &nickname);

    /**
     * Check if name is valid
     * @param name
     * @return true if valid
     */
    bool validateName(const std::string &name);

    /**
     * Check if birthday is valid
     * @param date
     * @return true if valid
     */
    bool validateBirthDate(const std::string &date);

    /**
     * Check if title is valid
     * @param title
     * @return true if valid
     */
    bool validateTitle(const std::string &title);
}


#endif //STREAMZ_INPUT_H
