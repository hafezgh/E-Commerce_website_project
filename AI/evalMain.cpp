#include "CommentEvaluatorAI.hpp"

using namespace std;

int main()
{
    string PcFilePath = "class probabilities";
    string trainDataFilePath = "train.csv";
    string testDataFilePath = "test.csv";
    CommentEvaluatorAI commentEval(PcFilePath, trainDataFilePath, testDataFilePath);
    commentEval.saveModelEvaluationResult();
    return 0;
}