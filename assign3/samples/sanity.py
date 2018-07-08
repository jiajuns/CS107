#!/usr/bin/python

class ExactMatchSoln(OutputDiffSoln):

    # Usual diff is insensitive to whitespace/blank lines, cat needs to be tested with _exact_ match
    def score(self, student, soln, context):
        if (student.output == soln.output):
            return results.Correct(score=1, short="Submission output matches sample", matched_output=student.output)
        return results.MismatchOutput(score=0, output=student.output, correct_output=soln.output)
