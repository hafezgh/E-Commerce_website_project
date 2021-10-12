#include "siteInterface.hpp"
#include "CommentEvaluatorAI.hpp"

using namespace std;

int main()
{
    CommentEvaluatorAI evaluator("class probabilities", "train.csv", "test.csv");
    evaluator.readPc("class probabilities");
    evaluator.readTrainData("train.csv");
    evaluator.readTestData("test.csv");
    evaluator.evaluateModelBasedOnTestTexts();
    evaluator.printModelEvaluationResult();
    return 0;
}