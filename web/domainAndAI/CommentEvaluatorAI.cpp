#include "CommentEvaluatorAI.hpp"


using namespace std;


CommentEvaluatorAI::CommentEvaluatorAI(std::string _PcFilePath, std::string _trainDataFilePath, std::string _testDataFilePath) 
{
    PcFilePath = _PcFilePath;
    trainDataFilePath = _trainDataFilePath;
    testDataFilePath = _testDataFilePath;
    trainEvaluator();
}

vector<string> CommentEvaluatorAI::parseCSVLine(string line)
{
    vector<string> parsedLine;
    stringstream ss(line);
    string substr;
    while(ss.good())
    {
        getline(ss, substr, COMMA);
        parsedLine.push_back(substr);
    }
    return parsedLine;
}

vector<string> CommentEvaluatorAI::commentParser(string comment)
{
    vector<string> parsedComment;
    stringstream ss(comment);
    string substr;
    while(ss.good())
    {
        getline(ss, substr, SPACE);
        parsedComment.push_back(substr);
    }
    return parsedComment;
}

void CommentEvaluatorAI::readTrainData(std::string filePath)
{
    ifstream fin(filePath);
    string line;
    vector<string> parsedLine;
    pair<long double, long double> probsTemp;
    getline(fin, line);
    while(getline(fin, line))
    {
        parsedLine.clear();
        parsedLine = parseCSVLine(line);
        goodProbsMap.insert(make_pair<string,long double>((parsedLine[0].c_str()), atof(parsedLine[1].c_str())));
        badProbsMap.insert(make_pair<string,long double>((parsedLine[0].c_str()), atof(parsedLine[2].c_str())));
    }
    fin.close();
}

void CommentEvaluatorAI::readTestData(std::string filePath)
{
    ifstream fin(filePath);
    string line;
    vector<string> parsedLine;
    getline(fin, line);
    while(getline(fin, line))
    {
        parsedLine.clear();
        parsedLine = parseCSVLine(line);
        testTexts.first.push_back(parsedLine[0]);
        testTexts.second.push_back(atoi(parsedLine[1].c_str()));
    }
    fin.close();
}

void CommentEvaluatorAI::readPc(string filePath)
{
    ifstream fin(filePath);
    string line;
    getline(fin, line);
    Pc = atof(line.c_str());
    fin.close();
}

bool CommentEvaluatorAI::evaluateComment(string comment)
{
    vector <string> parsedComment = commentParser(comment);
    long double loggedProbOfGood = 0;
    long double loggedProbOfBad = 0;
    for(int i = 0; i < parsedComment.size(); i++)
    {
        loggedProbOfGood += log(goodProbsMap[parsedComment[i]]);
        loggedProbOfBad += log(badProbsMap[parsedComment[i]]);
    }
    long double probOfGood = exp(loggedProbOfGood) * Pc;
    long double probOfBad = exp(loggedProbOfBad) * Pc;
    return probOfBad > probOfGood;
}

void CommentEvaluatorAI::evaluateModelBasedOnTestTexts()
{
    int numOfAllComments = testTexts.first.size();
    int numOfAllAppropriateComments = 0;
    int numOfCorrectDetectedComments = 0;
    int numOfCorrectDetectedAppropriateComments = 0;
    int numOfDetectedAppropriateComments = 0;
    bool detectedLabel;
    for(int i = 0; i < testTexts.first.size(); i++)
    {
        detectedLabel = evaluateComment(testTexts.first[i]);
        if(!(testTexts.second[i]))
        {
            numOfAllAppropriateComments++;
            if(!detectedLabel)
            {
                numOfCorrectDetectedComments++;
                numOfCorrectDetectedAppropriateComments++;
                numOfDetectedAppropriateComments++;
            }
            else
                numOfDetectedAppropriateComments++;
        }
        else
        {
            if(detectedLabel)
                numOfCorrectDetectedComments++;
            else
                numOfDetectedAppropriateComments++;
        }
        recall = double(numOfCorrectDetectedAppropriateComments)/double(numOfAllAppropriateComments);
        precision = double(numOfCorrectDetectedAppropriateComments)/double(numOfDetectedAppropriateComments);
        accuracy = double(numOfCorrectDetectedComments)/double(numOfAllComments);
    }
}

void CommentEvaluatorAI::printModelEvaluationResult()
{
    cout << "Recall: " << recall << endl << "Precision: " << precision << endl << "Accuracy: " << accuracy << endl;
}

void CommentEvaluatorAI::trainEvaluator()
{
    readPc(PcFilePath);
    readTrainData(trainDataFilePath);
    readTestData(testDataFilePath);
    evaluateModelBasedOnTestTexts();
}

void CommentEvaluatorAI::saveModelEvaluationResult()
{
    ofstream fout;
    fout.open("output.txt");
    fout << "Recall: " << recall * 100 << endl << "Precision: " << precision * 100 << endl << "Accuracy: " << accuracy * 100 << endl;
    fout.close();
}
