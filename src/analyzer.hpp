#pragma once

#include <vector>
#include <string>
#include <map>

#include "statistics.hpp"
#include "word_cloud.hpp"

class Analyzer
{
private:
    // List of pointers to Statistics for each file
    std::vector<Statistics *> stats;

    // List of filtered out words
    std::vector<std::wstring> filter;

    std::string source_path;

    bool case_sensitive;

public:
    /**
     * @brief  Constructs ::wstring over either a path to a file or a path to a directory.
     * @note   Only text files are supported. Directories are searched recursively.
     * 
     * @param  path: Path to a file or a directory
     * @param case_sensitive: Should case be ignored?
     */
    Analyzer(std::string file_path, bool case_sensitive);

    /**
     * @brief  Constructs ::wstring over either a path to a file or a path to a directory.
     * @note   Only text files are supported. Directories are searched recursively.
     * 
     * @param  path: Path to a file or a directory
     * @param  filter: Words to be filtered out of the analysis
     * @param  case_sensitive: Should case be ignored?
     */
    Analyzer(std::string path, std::vector<std::wstring> filter, bool case_sensitive);

    ~Analyzer();

    /**
     * @brief  Sets the list of filtered out words.
     * 
     * @param  filter: Vector of words to be filtered out
     */
    void set_filters(std::vector<std::wstring> filter);

    /**
     * @brief  Counts every word loaded from path.
     * @note   Discards filtered out words.
     * 
     * @retval Number of words in the path
     */
    long get_word_count();

    /**
     * @brief  Counts every unique word loaded from path.
     * @note   Discards filtered out words.
     * 
     * @retval Number of unique words in the path
     */
    long get_unique_word_count();

    /**
     * @brief  Counts every unique word loaded from per file.
     * @note   Discards filtered out words.
     * 
     * @retval Number of words in a file
     */
    std::vector<std::pair<std::string, long>> get_word_count_per_file();

    /**
     * @brief  Counts every unique word loaded per file.
     * @note   Discards filtered out words.
     */
    std::vector<std::pair<std::string, long>> get_unique_word_count_per_file();

    /**
     * @brief  Generates five most frequent n-grams.
     * @note   Discards filtered out words. Throws if set word is filtered out.
     * 
     * @param  size: Size of the n-gram (n)
     * 
     * @retval Vector of n_grams
     */
    std::vector<Statistics::n_gram> generate_n_gram(int size);

    /**
     * @brief  Generates five most frequent n-grams per file.
     * @note   Discards filtered out words. Throws if set word is filtered out.
     * 
     * @param  size: Size of the n-gram (n)
     * 
     * @retval Vector of pairs with file path as first and vector of n_grams as second
     */
    std::vector<std::pair<std::string, std::vector<Statistics::n_gram>>> generate_n_gram_per_file(int size);

    /**
     * @brief  Generates a word cloud.
     * @note   Discards filtered out words.
     */
    void generate_word_cloud();

    /**
     * @brief  Generates a word clouds per file.
     * @note   Discards filtered out words.
     */
    void generate_word_cloud_per_file();

private:
    /**
     * @brief Returns all of the words loaded by the analyzer.
     * 
     * @retval Vector of words in all of the files
     */
    std::vector<std::wstring> get_words();

    /**
     * @brief  Loads the file statistics.
     */
    void load();
};