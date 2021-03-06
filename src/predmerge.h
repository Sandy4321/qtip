#include <stdlib.h>
#include <vector>
#include <string>
#include <limits>

/**
 * A single MAPQ prediction and associated line number
 */
struct Prediction {
    Prediction() {
        reset();
    }

    Prediction(unsigned long long _line, double _mapq) : line(_line), mapq(_mapq) { }
	
	void reset() {
        line = std::numeric_limits<unsigned long long>::max();
        mapq = 0.0;
	}

    bool valid() const {
        return line != std::numeric_limits<unsigned long long>::max();
    }

    unsigned long long line;
    double mapq;
};

/**
 * Manages a collection of files, each with a series of predictions, in
 * ascending order by line number.  No line number should be repeated within
 * or across files.
 */
class PredictionMerger {
public:
    PredictionMerger(const std::vector<std::string>& in_fns);
	
	~PredictionMerger();

    Prediction next();

private:

    bool advanceFile(size_t i);

    const std::vector<std::string>& in_fns_;
    std::vector<FILE *> in_;
    std::vector<std::vector<char> > bufs_;
    std::vector<Prediction> preds_;
    std::vector<bool> done_;
    int next_; // -1 if next is unknown, index of next file to read from otherwise
};
