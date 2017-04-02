import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.positives = set()
        self.negatives = set()
        #self.tokenizer = nltk.tokenize.TweetTokenizer()  

        
        pfile = open(positives, "r")
        for line in pfile:
            if line.startswith(";") == False:
                self.positives.add(line.strip())
            else:
                continue
        pfile.close()
        
        nfile = open(negatives, "r")
        for line in nfile:
            if line.startswith(";") == False:
                self.negatives.add(line.strip())
            else:
                continue
        nfile.close()

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        
        total = 0
        self.tokenizer = nltk.tokenize.TweetTokenizer()  
        tokens = self.tokenizer.tokenize(text)
        
        #with open(text) as lines:
        #   for line in lines:
                
        
        for token in tokens:
            string = token.lower()
            if string.lower() in self.positives:
                total+= 1
            elif string.lower() in self.negatives:
                total -= 1
            else:
                total += 0
        return total
        