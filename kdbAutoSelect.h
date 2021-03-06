/* 
 * File:   kdbAutoSelectAutoSelect.h
 * Author: Administrator
 *
 * Created on 2018年3月21日, 下午6:52
 */
#pragma once

#include <limits.h>

#include "incrementalLearner.h"
#include "distributionTree.h"
#include "xxyDist.h"
#include "xxxyDist.h"
#include "yDist.h"


class kdbAutoSelect :  public IncrementalLearner
{
public:
  kdbAutoSelect();
  kdbAutoSelect(char*const*& argv, char*const* end);
  ~kdbAutoSelect(void);

  void reset(InstanceStream &is);   ///< reset the learner prior to training
  void initialisePass();            ///< must be called to initialise a pass through an instance stream before calling train(const instance). should not be used with train(InstanceStream)
  void train(const instance &inst); ///< primary training method. train from a single instance. used in conjunction with initialisePass and finalisePass
  void finalisePass();              ///< must be called to finalise a pass through an instance stream using train(const instance). should not be used with train(InstanceStream)
  bool trainingIsFinished();        ///< true iff no more passes are required. updated by finalisePass()
  void getCapabilities(capabilities &c);

  virtual void classify(const instance &inst, std::vector<double> &classDist);

protected:
  unsigned int pass_;                                        ///< the number of passes for the learner
  unsigned int k_;                                           ///< the maximum number of parents
  unsigned int noCatAtts_;                                   ///< the number of categorical attributes.
  unsigned int noClasses_;                                   ///< the number of classes
  bool union_kdb_kdbAutoSelect = false;
  
  
  xxyDist dist_;                                             // used in the first pass
  xxxyDist dist_1; 
  yDist classDist_;                                          // used in the second pass and for classification
  yDist classDist_1;   
  std::vector<CategoricalAttribute> order_;
  std::vector<distributionTree> dTree_;                      // used in the second pass and for classification
  
  std::vector<std::vector<CategoricalAttribute> > parents_;
  std::vector<std::vector<CategoricalAttribute> > parents_1;
  bool trainingIsFinished_;
  InstanceStream* instanceStream_;
};

