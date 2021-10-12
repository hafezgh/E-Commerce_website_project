#ifndef __EVALUATOR__
#define __EVALUATOR__

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <unordered_map>

#define COMMA ','
#define SPACE ' '

class CommentEvaluatorAI
{
public:
    CommentEvaluatorAI(std::string _PcFilePath, std::string _trainDataFilePath, std::string _testDataFilePath);
    void readTrainData(std::string filePath);
    void readTestData(std::string filePath);
    std::vector<std::string> parseCSVLine(std::string line);
    std::vector<std::string> commentParser(std::string comment);
    void readPc(std::string filePath);
    bool evaluateComment(std::string);
    void evaluateModelBasedOnTestTexts();
    void printModelEvaluationResult();
    void saveModelEvaluationResult();
    void trainEvaluator();
    std::string PcFilePath;
    std::string trainDataFilePath;
    std::string testDataFilePath;
private:
    long double Pc;
    std::unordered_map<std::string, long double> goodProbsMap;
    std::unordered_map<std::string, long double> badProbsMap;
    std::pair<std::vector<std::string>, std::vector<bool>> testTexts;
    long double recall;
    long double precision;
    long double accuracy;
};

#endif