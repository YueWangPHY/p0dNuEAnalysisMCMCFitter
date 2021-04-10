#ifndef BDTCLASSIFIER_H
#define BDTCLASSIFIER_H

class BDTClassifier {

 protected :
  float multiplier;

 public :
  union BDTClassifierFeature {
    int missing;
    float fvalue;
    int qvalue;
  };
  

  
  virtual size_t get_num_output_group(void) = 0;
  virtual size_t get_num_feature(void) = 0;
  
  virtual float predict(union BDTClassifier::BDTClassifierFeature* data, int pred_margin) = 0;

  bool GetClassfication(union BDTClassifier::BDTClassifierFeature* data, int pred_margin){ return multiplier*predict(data, pred_margin)>0.5; } //in BDT, use 0.5 as the cut for the prob. it can be changed based on the specific BDT used

 BDTClassifier() : multiplier (1.) {};
 BDTClassifier(float mult) : multiplier (mult) {};
  ~BDTClassifier(){};
  
};

#endif
