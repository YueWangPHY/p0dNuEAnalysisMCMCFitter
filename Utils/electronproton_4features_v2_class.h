
#include "BDTClassifier.h"
#include "math.h"
class electronproton_4features_v2_class : public BDTClassifier {
 public :
 electronproton_4features_v2_class() : BDTClassifier(1.) {;}
  ~electronproton_4features_v2_class() {;}


;

size_t get_num_output_group(void) {
  return 1;
}

size_t get_num_feature(void) {
  return 4;
}

const char* get_pred_transform(void) {
  return "sigmoid";
}

float get_sigmoid_alpha(void) {
  return 1.0;
}

float get_global_bias(void) {
  return -0.0;
}

static inline float pred_transform(float margin) {
  const float alpha = (float)1.0;
  return 1.0f / (1 + expf(-alpha * margin));
}
   float predict(union BDTClassifier::BDTClassifierFeature* data, int pred_margin) {

  float sum = 0.0f;
  unsigned int tmp;
  int nid, cond, fid;  /* used for folded subtrees */
  if ( (data[0].fvalue < (float)276.03601074)) {
    if ( (data[0].fvalue < (float)205.92700195)) {
      if ( (data[1].fvalue < (float)7.8817253113)) {
        sum += (float)-0.14480052888;
      } else {
        sum += (float)-0.18294526637;
      }
    } else {
      if ( (data[1].fvalue < (float)6.3171901703)) {
        sum += (float)-0.04716617614;
      } else {
        sum += (float)-0.13537015021;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)5.0721001625)) {
      if ( (data[2].fvalue < (float)2.5366699696)) {
        sum += (float)0.075116813183;
      } else {
        sum += (float)-0.10234840214;
      }
    } else {
      if ( (data[2].fvalue < (float)2.5162000656)) {
        sum += (float)-0.024164948612;
      } else {
        sum += (float)-0.13943941891;
      }
    }
  }
  if ( (data[0].fvalue < (float)283.27700806)) {
    if ( (data[0].fvalue < (float)207.51750183)) {
      if ( (data[1].fvalue < (float)10.548799515)) {
        sum += (float)-0.13594971597;
      } else {
        sum += (float)-0.16782996058;
      }
    } else {
      if ( (data[1].fvalue < (float)5.8535652161)) {
        sum += (float)-0.034288913012;
      } else {
        sum += (float)-0.11809720099;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)4.6989545822)) {
      if ( (data[2].fvalue < (float)2.5586500168)) {
        sum += (float)0.071606956422;
      } else {
        sum += (float)-0.096276067197;
      }
    } else {
      if ( (data[2].fvalue < (float)2.5162000656)) {
        sum += (float)-0.015703601763;
      } else {
        sum += (float)-0.1233009249;
      }
    }
  }
  if ( (data[0].fvalue < (float)259.27301025)) {
    if ( (data[1].fvalue < (float)7.6932001114)) {
      if ( (data[0].fvalue < (float)190.35350037)) {
        sum += (float)-0.12706282735;
      } else {
        sum += (float)-0.060718376189;
      }
    } else {
      if ( (data[0].fvalue < (float)184.78450012)) {
        sum += (float)-0.15496367216;
      } else {
        sum += (float)-0.12631833553;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)5.9740200043)) {
      if ( (data[2].fvalue < (float)2.5076799393)) {
        sum += (float)0.054017465562;
      } else {
        sum += (float)-0.085004106164;
      }
    } else {
      if ( (data[1].fvalue < (float)9.0431556702)) {
        sum += (float)-0.022898858413;
      } else {
        sum += (float)-0.088253222406;
      }
    }
  }
  if ( (data[0].fvalue < (float)288.44250488)) {
    if ( (data[0].fvalue < (float)219.68701172)) {
      if ( (data[1].fvalue < (float)10.64525032)) {
        sum += (float)-0.11031311005;
      } else {
        sum += (float)-0.14364928007;
      }
    } else {
      if ( (data[1].fvalue < (float)5.569319725)) {
        sum += (float)-0.018548432738;
      } else {
        sum += (float)-0.093176655471;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)3.9251198769)) {
      if ( (data[2].fvalue < (float)2.4589049816)) {
        sum += (float)0.070769481361;
      } else {
        sum += (float)-0.054344143718;
      }
    } else {
      if ( (data[2].fvalue < (float)2.5637099743)) {
        sum += (float)-0.0067329518497;
      } else {
        sum += (float)-0.11251207441;
      }
    }
  }
  if ( (data[0].fvalue < (float)258.60150146)) {
    if ( (data[0].fvalue < (float)181.23901367)) {
      if ( (data[1].fvalue < (float)4.7227449417)) {
        sum += (float)-0.10132686049;
      } else {
        sum += (float)-0.13486211002;
      }
    } else {
      if ( (data[1].fvalue < (float)5.9147748947)) {
        sum += (float)-0.043628480285;
      } else {
        sum += (float)-0.10406041145;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)6.8147802353)) {
      if ( (data[2].fvalue < (float)2.5601201057)) {
        sum += (float)0.038850147277;
      } else {
        sum += (float)-0.08357911557;
      }
    } else {
      if ( (data[1].fvalue < (float)9.7478103638)) {
        sum += (float)-0.031006684527;
      } else {
        sum += (float)-0.086052633822;
      }
    }
  }
  if ( (data[0].fvalue < (float)268.19650269)) {
    if ( (data[0].fvalue < (float)188.37950134)) {
      if ( (data[1].fvalue < (float)10.64525032)) {
        sum += (float)-0.10589897633;
      } else {
        sum += (float)-0.12949597836;
      }
    } else {
      if ( (data[3].fvalue < (float)1.7836849689)) {
        sum += (float)-0.048258628696;
      } else {
        sum += (float)-0.11102066189;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)3.3398399353)) {
      if ( (data[2].fvalue < (float)2.4098050594)) {
        sum += (float)0.06715477258;
      } else {
        sum += (float)-0.036671917886;
      }
    } else {
      if ( (data[2].fvalue < (float)2.4847350121)) {
        sum += (float)-0.0053659030236;
      } else {
        sum += (float)-0.090156786144;
      }
    }
  }
  if ( (data[0].fvalue < (float)301.43902588)) {
    if ( (data[1].fvalue < (float)9.0064096451)) {
      if ( (data[0].fvalue < (float)190.35350037)) {
        sum += (float)-0.096558988094;
      } else {
        sum += (float)-0.031965035945;
      }
    } else {
      if ( (data[0].fvalue < (float)221.64100647)) {
        sum += (float)-0.11996423453;
      } else {
        sum += (float)-0.086757689714;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)3.1712150574)) {
      if ( (data[2].fvalue < (float)2.5857150555)) {
        sum += (float)0.062506765127;
      } else {
        sum += (float)-0.058196652681;
      }
    } else {
      if ( (data[2].fvalue < (float)2.6000699997)) {
        sum += (float)0.0006234322791;
      } else {
        sum += (float)-0.094118252397;
      }
    }
  }
  if ( (data[0].fvalue < (float)246.2835083)) {
    if ( (data[1].fvalue < (float)10.598799706)) {
      if ( (data[0].fvalue < (float)167.24949646)) {
        sum += (float)-0.10041373968;
      } else {
        sum += (float)-0.054647173733;
      }
    } else {
      if ( (data[0].fvalue < (float)154.96350098)) {
        sum += (float)-0.1200882569;
      } else {
        sum += (float)-0.10101204365;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)7.681994915)) {
      if ( (data[2].fvalue < (float)2.4544200897)) {
        sum += (float)0.028623146936;
      } else {
        sum += (float)-0.054976779968;
      }
    } else {
      if ( (data[3].fvalue < (float)1.0697649717)) {
        sum += (float)-0.018021190539;
      } else {
        sum += (float)-0.065665848553;
      }
    }
  }
  if ( (data[0].fvalue < (float)246.76998901)) {
    if ( (data[1].fvalue < (float)6.6733951569)) {
      if ( (data[3].fvalue < (float)1.8565649986)) {
        sum += (float)-0.034368269145;
      } else {
        sum += (float)-0.08832565695;
      }
    } else {
      if ( (data[0].fvalue < (float)154.96350098)) {
        sum += (float)-0.11394355446;
      } else {
        sum += (float)-0.088348887861;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)5.2474851608)) {
      if ( (data[3].fvalue < (float)1.3023300171)) {
        sum += (float)0.065202653408;
      } else {
        sum += (float)0.0090311337262;
      }
    } else {
      if ( (data[1].fvalue < (float)8.6612348557)) {
        sum += (float)-0.01082171686;
      } else {
        sum += (float)-0.05849814415;
      }
    }
  }
  if ( (data[0].fvalue < (float)321.6835022)) {
    if ( (data[1].fvalue < (float)10.788099289)) {
      if ( (data[3].fvalue < (float)1.7672749758)) {
        sum += (float)-0.021207977086;
      } else {
        sum += (float)-0.075360663235;
      }
    } else {
      if ( (data[0].fvalue < (float)195.13049316)) {
        sum += (float)-0.10786370188;
      } else {
        sum += (float)-0.080700270832;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)2.713244915)) {
      if ( (data[2].fvalue < (float)2.386384964)) {
        sum += (float)0.062190718949;
      } else {
        sum += (float)-0.015369829722;
      }
    } else {
      if ( (data[2].fvalue < (float)2.6293950081)) {
        sum += (float)0.0049248714931;
      } else {
        sum += (float)-0.084105812013;
      }
    }
  }
  if ( (data[0].fvalue < (float)242.9624939)) {
    if ( (data[0].fvalue < (float)167.1210022)) {
      if ( (data[1].fvalue < (float)4.7227449417)) {
        sum += (float)-0.073517523706;
      } else {
        sum += (float)-0.10353711993;
      }
    } else {
      if ( (data[3].fvalue < (float)1.7835849524)) {
        sum += (float)-0.041085321456;
      } else {
        sum += (float)-0.090828284621;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)6.2139549255)) {
      if ( (data[3].fvalue < (float)1.2609950304)) {
        sum += (float)0.053585834801;
      } else {
        sum += (float)0.0036109925713;
      }
    } else {
      if ( (data[1].fvalue < (float)10.048299789)) {
        sum += (float)-0.018328431994;
      } else {
        sum += (float)-0.063807547092;
      }
    }
  }
  if ( (data[0].fvalue < (float)232.27600098)) {
    if ( (data[1].fvalue < (float)8.5036201477)) {
      if ( (data[0].fvalue < (float)167.28799438)) {
        sum += (float)-0.080143265426;
      } else {
        sum += (float)-0.035109430552;
      }
    } else {
      if ( (data[0].fvalue < (float)154.96350098)) {
        sum += (float)-0.10221920162;
      } else {
        sum += (float)-0.080151282251;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)4.0702500343)) {
      if ( (data[2].fvalue < (float)0.3241609931)) {
        sum += (float)-0.13185015321;
      } else {
        sum += (float)0.03443210572;
      }
    } else {
      if ( (data[2].fvalue < (float)2.4876949787)) {
        sum += (float)-0.010220132768;
      } else {
        sum += (float)-0.075961895287;
      }
    }
  }
  if ( (data[1].fvalue < (float)8.8460655212)) {
    if ( (data[2].fvalue < (float)2.3987948895)) {
      if ( (data[2].fvalue < (float)0.34362649918)) {
        sum += (float)-0.11127922684;
      } else {
        sum += (float)0.015403397381;
      }
    } else {
      if ( (data[0].fvalue < (float)336.2795105)) {
        sum += (float)-0.094976574183;
      } else {
        sum += (float)-0.032777372748;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)221.64100647)) {
      if ( (data[0].fvalue < (float)154.96350098)) {
        sum += (float)-0.098701454699;
      } else {
        sum += (float)-0.078647479415;
      }
    } else {
      if ( (data[3].fvalue < (float)1.068584919)) {
        sum += (float)-0.021124828607;
      } else {
        sum += (float)-0.060158688575;
      }
    }
  }
  if ( (data[0].fvalue < (float)224.1835022)) {
    if ( (data[0].fvalue < (float)153.95098877)) {
      if ( (data[1].fvalue < (float)13.856949806)) {
        sum += (float)-0.081385172904;
      } else {
        sum += (float)-0.097262576222;
      }
    } else {
      if ( (data[1].fvalue < (float)4.3073248863)) {
        sum += (float)-0.016025079414;
      } else {
        sum += (float)-0.068326033652;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)2.7054150105)) {
      if ( (data[3].fvalue < (float)1.396889925)) {
        sum += (float)0.070211730897;
      } else {
        sum += (float)0.016553876922;
      }
    } else {
      if ( (data[3].fvalue < (float)1.166934967)) {
        sum += (float)0.01810307987;
      } else {
        sum += (float)-0.023181209341;
      }
    }
  }
  if ( (data[0].fvalue < (float)326.10650635)) {
    if ( (data[1].fvalue < (float)11.392850876)) {
      if ( (data[2].fvalue < (float)2.3664250374)) {
        sum += (float)-0.023132631555;
      } else {
        sum += (float)-0.088530756533;
      }
    } else {
      if ( (data[0].fvalue < (float)154.96350098)) {
        sum += (float)-0.093057565391;
      } else {
        sum += (float)-0.069233477116;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.29522749782)) {
      if ( (data[2].fvalue < (float)0.20841249824)) {
        sum += (float)-0.15931716561;
      } else {
        sum += (float)-0.077622048557;
      }
    } else {
      if ( (data[3].fvalue < (float)1.1695200205)) {
        sum += (float)0.048344064504;
      } else {
        sum += (float)0.00056886096718;
      }
    }
  }
  if ( (data[1].fvalue < (float)8.0343151093)) {
    if ( (data[2].fvalue < (float)2.6150000095)) {
      if ( (data[2].fvalue < (float)0.36983197927)) {
        sum += (float)-0.090706028044;
      } else {
        sum += (float)0.014218496159;
      }
    } else {
      if ( (data[0].fvalue < (float)409.93048096)) {
        sum += (float)-0.095944754779;
      } else {
        sum += (float)-0.048107020557;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)209.86898804)) {
      if ( (data[0].fvalue < (float)154.96350098)) {
        sum += (float)-0.088611774147;
      } else {
        sum += (float)-0.068273097277;
      }
    } else {
      if ( (data[2].fvalue < (float)2.3688950539)) {
        sum += (float)-0.032373741269;
      } else {
        sum += (float)-0.082211136818;
      }
    }
  }
  if ( (data[0].fvalue < (float)222.90750122)) {
    if ( (data[0].fvalue < (float)153.95098877)) {
      if ( (data[1].fvalue < (float)14.660900116)) {
        sum += (float)-0.073662318289;
      } else {
        sum += (float)-0.088192783296;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8723950386)) {
        sum += (float)-0.034031763673;
      } else {
        sum += (float)-0.077283501625;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)2.9132599831)) {
      if ( (data[3].fvalue < (float)1.3471649885)) {
        sum += (float)0.062389951199;
      } else {
        sum += (float)0.014356361702;
      }
    } else {
      if ( (data[3].fvalue < (float)1.1351950169)) {
        sum += (float)0.01568717137;
      } else {
        sum += (float)-0.019851116464;
      }
    }
  }
  if ( (data[1].fvalue < (float)9.8225593567)) {
    if ( (data[2].fvalue < (float)2.6381249428)) {
      if ( (data[2].fvalue < (float)0.41026598215)) {
        sum += (float)-0.076555721462;
      } else {
        sum += (float)0.0095683475956;
      }
    } else {
      if ( (data[0].fvalue < (float)411.58099365)) {
        sum += (float)-0.092637568712;
      } else {
        sum += (float)-0.048519764096;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)13.919799805)) {
      if ( (data[3].fvalue < (float)1.8048100471)) {
        sum += (float)-0.033914517611;
      } else {
        sum += (float)-0.068791463971;
      }
    } else {
      if ( (data[0].fvalue < (float)149.58650208)) {
        sum += (float)-0.085305549204;
      } else {
        sum += (float)-0.068126119673;
      }
    }
  }
  if ( (data[0].fvalue < (float)328.878479)) {
    if ( (data[0].fvalue < (float)181.23901367)) {
      if ( (data[0].fvalue < (float)142.23001099)) {
        sum += (float)-0.079192310572;
      } else {
        sum += (float)-0.056668139994;
      }
    } else {
      if ( (data[3].fvalue < (float)1.7569149733)) {
        sum += (float)-0.0078504327685;
      } else {
        sum += (float)-0.054122190922;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.31988200545)) {
      if ( (data[2].fvalue < (float)0.20841249824)) {
        sum += (float)-0.13021451235;
      } else {
        sum += (float)-0.052347172052;
      }
    } else {
      if ( (data[3].fvalue < (float)1.1681649685)) {
        sum += (float)0.042371418327;
      } else {
        sum += (float)0.0011931123445;
      }
    }
  }
  if ( (data[1].fvalue < (float)8.0301055908)) {
    if ( (data[2].fvalue < (float)2.6376750469)) {
      if ( (data[1].fvalue < (float)2.3604998589)) {
        sum += (float)0.038298707455;
      } else {
        sum += (float)-0.00010792881221;
      }
    } else {
      if ( (data[0].fvalue < (float)465.27752686)) {
        sum += (float)-0.079376757145;
      } else {
        sum += (float)-0.036851592362;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)12.718450546)) {
      if ( (data[2].fvalue < (float)2.5114500523)) {
        sum += (float)-0.026737395674;
      } else {
        sum += (float)-0.080527961254;
      }
    } else {
      if ( (data[0].fvalue < (float)149.58650208)) {
        sum += (float)-0.079057782888;
      } else {
        sum += (float)-0.060114979744;
      }
    }
  }
  if ( (data[0].fvalue < (float)217.12600708)) {
    if ( (data[0].fvalue < (float)153.95098877)) {
      if ( (data[1].fvalue < (float)21.832649231)) {
        sum += (float)-0.065649732947;
      } else {
        sum += (float)-0.078710064292;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8723950386)) {
        sum += (float)-0.027229437605;
      } else {
        sum += (float)-0.067402936518;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)5.5086097717)) {
      if ( (data[3].fvalue < (float)1.2649450302)) {
        sum += (float)0.040315609425;
      } else {
        sum += (float)0.0031147848349;
      }
    } else {
      if ( (data[2].fvalue < (float)0.31533300877)) {
        sum += (float)-0.10024102032;
      } else {
        sum += (float)-0.013510215096;
      }
    }
  }
  if ( (data[0].fvalue < (float)338.63400269)) {
    if ( (data[0].fvalue < (float)181.23901367)) {
      if ( (data[0].fvalue < (float)133.10900879)) {
        sum += (float)-0.071621321142;
      } else {
        sum += (float)-0.049884937704;
      }
    } else {
      if ( (data[3].fvalue < (float)1.741204977)) {
        sum += (float)-0.0049415524118;
      } else {
        sum += (float)-0.045339941978;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.27428948879)) {
      if ( (data[2].fvalue < (float)0.19881999493)) {
        sum += (float)-0.12275594473;
      } else {
        sum += (float)-0.056662011892;
      }
    } else {
      if ( (data[3].fvalue < (float)1.0616149902)) {
        sum += (float)0.038506776094;
      } else {
        sum += (float)0.003320341697;
      }
    }
  }
  if ( (data[1].fvalue < (float)10.086700439)) {
    if ( (data[2].fvalue < (float)0.42657449841)) {
      if ( (data[2].fvalue < (float)0.22031599283)) {
        sum += (float)-0.11192654818;
      } else {
        sum += (float)-0.045749314129;
      }
    } else {
      if ( (data[3].fvalue < (float)1.0564849377)) {
        sum += (float)0.04001474008;
      } else {
        sum += (float)-0.0053640310653;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)15.119750023)) {
      if ( (data[3].fvalue < (float)1.806704998)) {
        sum += (float)-0.027206335217;
      } else {
        sum += (float)-0.058464240283;
      }
    } else {
      if ( (data[0].fvalue < (float)133.12850952)) {
        sum += (float)-0.072322234511;
      } else {
        sum += (float)-0.058682799339;
      }
    }
  }
  if ( (data[0].fvalue < (float)210.89898682)) {
    if ( (data[0].fvalue < (float)142.23001099)) {
      if ( (data[1].fvalue < (float)21.832649231)) {
        sum += (float)-0.059728641063;
      } else {
        sum += (float)-0.07073430717;
      }
    } else {
      if ( (data[3].fvalue < (float)1.7835849524)) {
        sum += (float)-0.024482646957;
      } else {
        sum += (float)-0.058722682297;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)2.4940948486)) {
      if ( (data[2].fvalue < (float)2.3626050949)) {
        sum += (float)0.037714954466;
      } else {
        sum += (float)-0.017010049894;
      }
    } else {
      if ( (data[2].fvalue < (float)2.6157999039)) {
        sum += (float)-0.002872486366;
      } else {
        sum += (float)-0.064350135624;
      }
    }
  }
  if ( (data[1].fvalue < (float)7.6819448471)) {
    if ( (data[2].fvalue < (float)0.45757001638)) {
      if ( (data[2].fvalue < (float)0.23408699036)) {
        sum += (float)-0.10056511313;
      } else {
        sum += (float)-0.036704231054;
      }
    } else {
      if ( (data[3].fvalue < (float)1.0564849377)) {
        sum += (float)0.043852739036;
      } else {
        sum += (float)-0.00099109543953;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)12.718450546)) {
      if ( (data[2].fvalue < (float)2.4876949787)) {
        sum += (float)-0.018475530669;
      } else {
        sum += (float)-0.068335309625;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8354449272)) {
        sum += (float)-0.049818973988;
      } else {
        sum += (float)-0.068732343614;
      }
    }
  }
  if ( (data[0].fvalue < (float)344.4119873)) {
    if ( (data[0].fvalue < (float)169.98550415)) {
      if ( (data[0].fvalue < (float)133.10900879)) {
        sum += (float)-0.061344433576;
      } else {
        sum += (float)-0.043070297688;
      }
    } else {
      if ( (data[2].fvalue < (float)2.3274149895)) {
        sum += (float)-0.010221506469;
      } else {
        sum += (float)-0.062485914677;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)1.8128199577)) {
      if ( (data[3].fvalue < (float)1.4597200155)) {
        sum += (float)0.058945436031;
      } else {
        sum += (float)0.023089945316;
      }
    } else {
      if ( (data[2].fvalue < (float)2.6785149574)) {
        sum += (float)0.0061069792137;
      } else {
        sum += (float)-0.053638853133;
      }
    }
  }
  if ( (data[1].fvalue < (float)7.2069654465)) {
    if ( (data[2].fvalue < (float)0.410187006)) {
      if ( (data[2].fvalue < (float)0.18280100822)) {
        sum += (float)-0.11191673577;
      } else {
        sum += (float)-0.042328350246;
      }
    } else {
      if ( (data[3].fvalue < (float)1.1348800659)) {
        sum += (float)0.035937655717;
      } else {
        sum += (float)-0.00074081955245;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)12.718450546)) {
      if ( (data[2].fvalue < (float)2.5573000908)) {
        sum += (float)-0.015366153792;
      } else {
        sum += (float)-0.065948404372;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8354449272)) {
        sum += (float)-0.044397037476;
      } else {
        sum += (float)-0.063450120389;
      }
    }
  }
  if ( (data[0].fvalue < (float)195.07749939)) {
    if ( (data[0].fvalue < (float)142.23001099)) {
      if ( (data[3].fvalue < (float)1.4083850384)) {
        sum += (float)-0.062248516828;
      } else {
        sum += (float)-0.04937466979;
      }
    } else {
      if ( (data[3].fvalue < (float)1.2742900848)) {
        sum += (float)-0.051907639951;
      } else {
        sum += (float)-0.020384503528;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)2.6381249428)) {
      if ( (data[1].fvalue < (float)4.0718545914)) {
        sum += (float)0.020271988586;
      } else {
        sum += (float)-0.0062134191394;
      }
    } else {
      if ( (data[0].fvalue < (float)409.94549561)) {
        sum += (float)-0.076318196952;
      } else {
        sum += (float)-0.03295315057;
      }
    }
  }
  if ( (data[0].fvalue < (float)344.4119873)) {
    if ( (data[0].fvalue < (float)155.63749695)) {
      if ( (data[3].fvalue < (float)1.2064800262)) {
        sum += (float)-0.0605266653;
      } else {
        sum += (float)-0.044407371432;
      }
    } else {
      if ( (data[2].fvalue < (float)2.3776049614)) {
        sum += (float)-0.0095374025404;
      } else {
        sum += (float)-0.059166986495;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)1.8128199577)) {
      if ( (data[3].fvalue < (float)1.4597200155)) {
        sum += (float)0.052364911884;
      } else {
        sum += (float)0.019768100232;
      }
    } else {
      if ( (data[3].fvalue < (float)2.0076351166)) {
        sum += (float)-0.0036777320784;
      } else {
        sum += (float)0.02077347599;
      }
    }
  }
  if ( (data[0].fvalue < (float)239.29998779)) {
    if ( (data[1].fvalue < (float)2.7877700329)) {
      if ( (data[2].fvalue < (float)0.48643150926)) {
        sum += (float)-0.064708903432;
      } else {
        sum += (float)0.020181478932;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8504749537)) {
        sum += (float)-0.027943028137;
      } else {
        sum += (float)-0.053683627397;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.3198390007)) {
      if ( (data[0].fvalue < (float)342.01300049)) {
        sum += (float)-0.11154073477;
      } else {
        sum += (float)-0.056717045605;
      }
    } else {
      if ( (data[3].fvalue < (float)0.95154547691)) {
        sum += (float)0.033270336688;
      } else {
        sum += (float)-0.0024553842377;
      }
    }
  }
  if ( (data[1].fvalue < (float)6.4007148743)) {
    if ( (data[2].fvalue < (float)0.45756947994)) {
      if ( (data[2].fvalue < (float)0.18280100822)) {
        sum += (float)-0.10034268349;
      } else {
        sum += (float)-0.035056840628;
      }
    } else {
      if ( (data[3].fvalue < (float)1.1595649719)) {
        sum += (float)0.036411669105;
      } else {
        sum += (float)0.00065677351085;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)11.715450287)) {
      if ( (data[2].fvalue < (float)0.36160099506)) {
        sum += (float)-0.065528586507;
      } else {
        sum += (float)-0.010064717382;
      }
    } else {
      if ( (data[3].fvalue < (float)1.85029006)) {
        sum += (float)-0.032267075032;
      } else {
        sum += (float)-0.05352947861;
      }
    }
  }
  if ( (data[0].fvalue < (float)344.4119873)) {
    if ( (data[2].fvalue < (float)0.51392555237)) {
      if ( (data[2].fvalue < (float)0.28640401363)) {
        sum += (float)-0.093179859221;
      } else {
        sum += (float)-0.051648970693;
      }
    } else {
      if ( (data[3].fvalue < (float)0.82291847467)) {
        sum += (float)0.028166193515;
      } else {
        sum += (float)-0.020860275254;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)2.6651649475)) {
      if ( (data[3].fvalue < (float)2.007735014)) {
        sum += (float)0.0010525247781;
      } else {
        sum += (float)0.032039228827;
      }
    } else {
      if ( (data[0].fvalue < (float)512.63146973)) {
        sum += (float)-0.055000174791;
      } else {
        sum += (float)-0.018624061719;
      }
    }
  }
  if ( (data[1].fvalue < (float)5.2475347519)) {
    if ( (data[2].fvalue < (float)2.3840649128)) {
      if ( (data[2].fvalue < (float)0.49031749368)) {
        sum += (float)-0.038426302373;
      } else {
        sum += (float)0.01774032414;
      }
    } else {
      if ( (data[2].fvalue < (float)2.7134699821)) {
        sum += (float)-0.012002145872;
      } else {
        sum += (float)-0.047533892095;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)223.58300781)) {
      if ( (data[3].fvalue < (float)1.3449749947)) {
        sum += (float)-0.048435240984;
      } else {
        sum += (float)-0.02593855001;
      }
    } else {
      if ( (data[3].fvalue < (float)0.7830965519)) {
        sum += (float)0.017526095733;
      } else {
        sum += (float)-0.012193762697;
      }
    }
  }
  if ( (data[1].fvalue < (float)2.7054150105)) {
    if ( (data[3].fvalue < (float)1.3933250904)) {
      if ( (data[2].fvalue < (float)0.4883595109)) {
        sum += (float)-0.023046176881;
      } else {
        sum += (float)0.047834694386;
      }
    } else {
      if ( (data[2].fvalue < (float)2.5978651047)) {
        sum += (float)0.011942549609;
      } else {
        sum += (float)-0.02945218049;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)195.14950562)) {
      if ( (data[3].fvalue < (float)1.283254981)) {
        sum += (float)-0.049562450498;
      } else {
        sum += (float)-0.026317438111;
      }
    } else {
      if ( (data[2].fvalue < (float)0.36160099506)) {
        sum += (float)-0.058698922396;
      } else {
        sum += (float)-0.0023979204707;
      }
    }
  }
  if ( (data[0].fvalue < (float)363.11102295)) {
    if ( (data[2].fvalue < (float)2.2871000767)) {
      if ( (data[2].fvalue < (float)0.45811349154)) {
        sum += (float)-0.059692662209;
      } else {
        sum += (float)-0.0055914758705;
      }
    } else {
      if ( (data[2].fvalue < (float)2.6547551155)) {
        sum += (float)-0.034006923437;
      } else {
        sum += (float)-0.064432762563;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)1.7021150589)) {
      if ( (data[3].fvalue < (float)1.4890400171)) {
        sum += (float)0.046640053391;
      } else {
        sum += (float)0.017932835966;
      }
    } else {
      if ( (data[3].fvalue < (float)2.0076351166)) {
        sum += (float)-0.0036552138627;
      } else {
        sum += (float)0.019327465445;
      }
    }
  }
  if ( (data[0].fvalue < (float)184.09049988)) {
    if ( (data[3].fvalue < (float)1.3554099798)) {
      if ( (data[1].fvalue < (float)1.346339941)) {
        sum += (float)0.077664859593;
      } else {
        sum += (float)-0.045135036111;
      }
    } else {
      if ( (data[3].fvalue < (float)1.665109992)) {
        sum += (float)0.02115679346;
      } else {
        sum += (float)-0.035307355225;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)2.3943550587)) {
      if ( (data[3].fvalue < (float)2.2006800175)) {
        sum += (float)0.00012408939074;
      } else {
        sum += (float)0.035353664309;
      }
    } else {
      if ( (data[0].fvalue < (float)299.30200195)) {
        sum += (float)-0.060883879662;
      } else {
        sum += (float)-0.018074966967;
      }
    }
  }
  if ( (data[1].fvalue < (float)4.482049942)) {
    if ( (data[3].fvalue < (float)1.3475849628)) {
      if ( (data[2].fvalue < (float)0.51238644123)) {
        sum += (float)-0.027520811185;
      } else {
        sum += (float)0.036015164107;
      }
    } else {
      if ( (data[2].fvalue < (float)2.6374049187)) {
        sum += (float)0.0039825043641;
      } else {
        sum += (float)-0.034271389246;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)248.35049438)) {
      if ( (data[3].fvalue < (float)1.7988500595)) {
        sum += (float)-0.016693467274;
      } else {
        sum += (float)-0.042967159301;
      }
    } else {
      if ( (data[3].fvalue < (float)0.78330349922)) {
        sum += (float)0.017933275551;
      } else {
        sum += (float)-0.0082567445934;
      }
    }
  }
  if ( (data[1].fvalue < (float)2.1029548645)) {
    if ( (data[3].fvalue < (float)1.4596999884)) {
      if ( (data[2].fvalue < (float)0.48380148411)) {
        sum += (float)-0.016615612432;
      } else {
        sum += (float)0.044442992657;
      }
    } else {
      if ( (data[3].fvalue < (float)1.6846199036)) {
        sum += (float)-0.01877059415;
      } else {
        sum += (float)0.015840318054;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)155.63749695)) {
      if ( (data[3].fvalue < (float)1.4083850384)) {
        sum += (float)-0.04392619431;
      } else {
        sum += (float)-0.026435820386;
      }
    } else {
      if ( (data[2].fvalue < (float)2.5669798851)) {
        sum += (float)-0.0010332183447;
      } else {
        sum += (float)-0.039521683007;
      }
    }
  }
  if ( (data[1].fvalue < (float)10.81055069)) {
    if ( (data[2].fvalue < (float)0.23408900201)) {
      if ( (data[2].fvalue < (float)0.15581950545)) {
        sum += (float)-0.094300270081;
      } else {
        sum += (float)-0.055123027414;
      }
    } else {
      if ( (data[3].fvalue < (float)0.88287103176)) {
        sum += (float)0.02408814989;
      } else {
        sum += (float)-0.0021648097318;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)1.8047950268)) {
      if ( (data[3].fvalue < (float)1.4408500195)) {
        sum += (float)-0.030433634296;
      } else {
        sum += (float)0.021438201889;
      }
    } else {
      if ( (data[1].fvalue < (float)11.392999649)) {
        sum += (float)-0.023632848635;
      } else {
        sum += (float)-0.040567640215;
      }
    }
  }
  if ( (data[1].fvalue < (float)1.5871100426)) {
    if ( (data[3].fvalue < (float)1.396690011)) {
      if ( (data[2].fvalue < (float)0.64139598608)) {
        sum += (float)0.00081332115224;
      } else {
        sum += (float)0.053073983639;
      }
    } else {
      if ( (data[3].fvalue < (float)1.6507599354)) {
        sum += (float)-0.013149752282;
      } else {
        sum += (float)0.021407594904;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.51871645451)) {
      if ( (data[2].fvalue < (float)0.20841249824)) {
        sum += (float)-0.078570343554;
      } else {
        sum += (float)-0.027734145522;
      }
    } else {
      if ( (data[3].fvalue < (float)0.93087649345)) {
        sum += (float)0.024402685463;
      } else {
        sum += (float)-0.0070150136016;
      }
    }
  }
  if ( (data[0].fvalue < (float)363.11102295)) {
    if ( (data[3].fvalue < (float)1.6773149967)) {
      if ( (data[2].fvalue < (float)0.57201749086)) {
        sum += (float)-0.041087955236;
      } else {
        sum += (float)0.004415019881;
      }
    } else {
      if ( (data[2].fvalue < (float)2.5923199654)) {
        sum += (float)-0.017985863611;
      } else {
        sum += (float)-0.050050903112;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)1.9531300068)) {
      if ( (data[3].fvalue < (float)1.3474500179)) {
        sum += (float)0.012027893215;
      } else {
        sum += (float)-0.015697589144;
      }
    } else {
      if ( (data[2].fvalue < (float)2.3943550587)) {
        sum += (float)0.037595216185;
      } else {
        sum += (float)-0.013573743403;
      }
    }
  }
  if ( (data[1].fvalue < (float)5.6235799789)) {
    if ( (data[2].fvalue < (float)2.3274400234)) {
      if ( (data[3].fvalue < (float)2.2006700039)) {
        sum += (float)0.0058070374653;
      } else {
        sum += (float)0.038328345865;
      }
    } else {
      if ( (data[2].fvalue < (float)2.7562050819)) {
        sum += (float)-0.0072365961969;
      } else {
        sum += (float)-0.040898688138;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)12.718450546)) {
      if ( (data[2].fvalue < (float)0.2953684926)) {
        sum += (float)-0.061535842717;
      } else {
        sum += (float)-0.0048490348272;
      }
    } else {
      if ( (data[3].fvalue < (float)1.3449549675)) {
        sum += (float)-0.037498723716;
      } else {
        sum += (float)-0.017416132614;
      }
    }
  }
  if ( (data[1].fvalue < (float)2.3604998589)) {
    if ( (data[3].fvalue < (float)1.4890400171)) {
      if ( (data[2].fvalue < (float)0.48096901178)) {
        sum += (float)-0.014748349786;
      } else {
        sum += (float)0.035304129124;
      }
    } else {
      if ( (data[3].fvalue < (float)1.6663050652)) {
        sum += (float)-0.02295047231;
      } else {
        sum += (float)0.010231834836;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.54987347126)) {
      if ( (data[2].fvalue < (float)0.20841249824)) {
        sum += (float)-0.074333503842;
      } else {
        sum += (float)-0.024150185287;
      }
    } else {
      if ( (data[3].fvalue < (float)0.79207801819)) {
        sum += (float)0.027270216495;
      } else {
        sum += (float)-0.0059630875476;
      }
    }
  }
  if ( (data[0].fvalue < (float)155.63749695)) {
    if ( (data[3].fvalue < (float)1.4083850384)) {
      if ( (data[0].fvalue < (float)46.248950958)) {
        sum += (float)-0.0083495145664;
      } else {
        sum += (float)-0.043509956449;
      }
    } else {
      if ( (data[3].fvalue < (float)1.6436049938)) {
        sum += (float)0.0091417869553;
      } else {
        sum += (float)-0.02569049038;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)2.6938450336)) {
      if ( (data[2].fvalue < (float)0.46617150307)) {
        sum += (float)-0.028569234535;
      } else {
        sum += (float)0.0039233574644;
      }
    } else {
      if ( (data[0].fvalue < (float)512.63146973)) {
        sum += (float)-0.050004340708;
      } else {
        sum += (float)-0.0084215439856;
      }
    }
  }
  if ( (data[1].fvalue < (float)1.5871100426)) {
    if ( (data[3].fvalue < (float)1.3962199688)) {
      if ( (data[2].fvalue < (float)0.71021801233)) {
        sum += (float)0.0046487902291;
      } else {
        sum += (float)0.04667685926;
      }
    } else {
      if ( (data[3].fvalue < (float)1.6507599354)) {
        sum += (float)-0.011449811049;
      } else {
        sum += (float)0.018179042265;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)2.678550005)) {
      if ( (data[0].fvalue < (float)142.23001099)) {
        sum += (float)-0.029246954247;
      } else {
        sum += (float)-0.00025094352895;
      }
    } else {
      if ( (data[0].fvalue < (float)464.84747314)) {
        sum += (float)-0.050259437412;
      } else {
        sum += (float)-0.013493123464;
      }
    }
  }
  if ( (data[0].fvalue < (float)377.54699707)) {
    if ( (data[2].fvalue < (float)2.2651948929)) {
      if ( (data[2].fvalue < (float)0.37050899863)) {
        sum += (float)-0.052616115659;
      } else {
        sum += (float)-0.0024644020014;
      }
    } else {
      if ( (data[0].fvalue < (float)289.92901611)) {
        sum += (float)-0.0375418365;
      } else {
        sum += (float)-0.016025386751;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)1.9863950014)) {
      if ( (data[3].fvalue < (float)1.3023250103)) {
        sum += (float)0.011196696199;
      } else {
        sum += (float)-0.012146867812;
      }
    } else {
      if ( (data[2].fvalue < (float)2.398624897)) {
        sum += (float)0.035491660237;
      } else {
        sum += (float)-0.0095035033301;
      }
    }
  }
  if ( (data[1].fvalue < (float)3.5367200375)) {
    if ( (data[3].fvalue < (float)1.2486050129)) {
      if ( (data[2].fvalue < (float)0.64918005466)) {
        sum += (float)-0.0076836133376;
      } else {
        sum += (float)0.037964165211;
      }
    } else {
      if ( (data[1].fvalue < (float)1.5092549324)) {
        sum += (float)0.012680329382;
      } else {
        sum += (float)-0.0023272321559;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)309.48150635)) {
      if ( (data[3].fvalue < (float)1.7892849445)) {
        sum += (float)-0.0040568532422;
      } else {
        sum += (float)-0.029837364331;
      }
    } else {
      if ( (data[3].fvalue < (float)2.0119349957)) {
        sum += (float)-0.0070611848496;
      } else {
        sum += (float)0.018358107656;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.26952499151)) {
    if ( (data[2].fvalue < (float)0.15581950545)) {
      if ( (data[1].fvalue < (float)23.173250198)) {
        sum += (float)-0.078706368804;
      } else {
        sum += (float)0.064260721207;
      }
    } else {
      if ( (data[0].fvalue < (float)386.89898682)) {
        sum += (float)-0.064391173422;
      } else {
        sum += (float)-0.012210451998;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.78330552578)) {
      if ( (data[0].fvalue < (float)193.52749634)) {
        sum += (float)-0.033054057509;
      } else {
        sum += (float)0.025077862665;
      }
    } else {
      if ( (data[0].fvalue < (float)377.54699707)) {
        sum += (float)-0.0096415597945;
      } else {
        sum += (float)0.0031182693783;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.61103951931)) {
    if ( (data[2].fvalue < (float)0.18280100822)) {
      if ( (data[0].fvalue < (float)126.97250366)) {
        sum += (float)0.045421592891;
      } else {
        sum += (float)-0.069271892309;
      }
    } else {
      if ( (data[0].fvalue < (float)287.86099243)) {
        sum += (float)-0.03518981114;
      } else {
        sum += (float)-0.0079287420958;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.94822651148)) {
      if ( (data[0].fvalue < (float)186.40350342)) {
        sum += (float)-0.035403292626;
      } else {
        sum += (float)0.030945179984;
      }
    } else {
      if ( (data[2].fvalue < (float)2.694175005)) {
        sum += (float)-0.0014926872682;
      } else {
        sum += (float)-0.030892148614;
      }
    }
  }
  if ( (data[1].fvalue < (float)4.482049942)) {
    if ( (data[3].fvalue < (float)1.2486050129)) {
      if ( (data[2].fvalue < (float)0.67900002003)) {
        sum += (float)-0.0089707607403;
      } else {
        sum += (float)0.031541604549;
      }
    } else {
      if ( (data[2].fvalue < (float)2.7562050819)) {
        sum += (float)0.0025087178219;
      } else {
        sum += (float)-0.028332445771;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.58260953426)) {
      if ( (data[2].fvalue < (float)0.53683751822)) {
        sum += (float)-0.012480072677;
      } else {
        sum += (float)0.027566587552;
      }
    } else {
      if ( (data[2].fvalue < (float)0.65722703934)) {
        sum += (float)-0.03188572824;
      } else {
        sum += (float)-0.0050400770269;
      }
    }
  }
  if ( (data[1].fvalue < (float)1.8408449888)) {
    if ( (data[3].fvalue < (float)1.489675045)) {
      if ( (data[2].fvalue < (float)0.7789440155)) {
        sum += (float)0.0052466518246;
      } else {
        sum += (float)0.034080907702;
      }
    } else {
      if ( (data[3].fvalue < (float)1.6507599354)) {
        sum += (float)-0.025084737688;
      } else {
        sum += (float)0.012692551129;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.26952499151)) {
      if ( (data[0].fvalue < (float)385.80102539)) {
        sum += (float)-0.065306581557;
      } else {
        sum += (float)-0.026925761253;
      }
    } else {
      if ( (data[3].fvalue < (float)0.69352900982)) {
        sum += (float)0.016103295609;
      } else {
        sum += (float)-0.0040381359868;
      }
    }
  }
  if ( (data[1].fvalue < (float)6.931895256)) {
    if ( (data[3].fvalue < (float)1.248149991)) {
      if ( (data[2].fvalue < (float)0.67919450998)) {
        sum += (float)-0.010575152934;
      } else {
        sum += (float)0.021516846493;
      }
    } else {
      if ( (data[3].fvalue < (float)2.0076599121)) {
        sum += (float)-0.0084251649678;
      } else {
        sum += (float)0.010068716481;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)2.6013450623)) {
      if ( (data[1].fvalue < (float)14.974300385)) {
        sum += (float)-0.0039070500061;
      } else {
        sum += (float)-0.021200953051;
      }
    } else {
      if ( (data[0].fvalue < (float)134.39849854)) {
        sum += (float)-0.00037099831388;
      } else {
        sum += (float)-0.042788121849;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.3840649128)) {
    if ( (data[3].fvalue < (float)2.2454850674)) {
      if ( (data[1].fvalue < (float)2.7041699886)) {
        sum += (float)0.0097678443417;
      } else {
        sum += (float)-0.0043038697913;
      }
    } else {
      if ( (data[0].fvalue < (float)283.34500122)) {
        sum += (float)-0.014583661221;
      } else {
        sum += (float)0.039250116795;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)431.08850098)) {
      if ( (data[2].fvalue < (float)2.8034050465)) {
        sum += (float)-0.020300392061;
      } else {
        sum += (float)-0.048034086823;
      }
    } else {
      if ( (data[3].fvalue < (float)2.4860448837)) {
        sum += (float)0.0095123229548;
      } else {
        sum += (float)-0.015443558805;
      }
    }
  }
  if ( (data[0].fvalue < (float)133.10900879)) {
    if ( (data[3].fvalue < (float)1.7544850111)) {
      if ( (data[2].fvalue < (float)0.34270450473)) {
        sum += (float)0.039551399648;
      } else {
        sum += (float)-0.031995903701;
      }
    } else {
      if ( (data[1].fvalue < (float)49.707603455)) {
        sum += (float)-0.0046591754071;
      } else {
        sum += (float)-0.036030042917;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)2.3032050133)) {
      if ( (data[3].fvalue < (float)2.1998898983)) {
        sum += (float)-0.00027036687243;
      } else {
        sum += (float)0.028305187821;
      }
    } else {
      if ( (data[0].fvalue < (float)285.54449463)) {
        sum += (float)-0.038088746369;
      } else {
        sum += (float)-0.0065393089317;
      }
    }
  }
  if ( (data[1].fvalue < (float)1.5106250048)) {
    if ( (data[3].fvalue < (float)1.3962199688)) {
      if ( (data[2].fvalue < (float)1.0575100183)) {
        sum += (float)0.013545244932;
      } else {
        sum += (float)0.042621955276;
      }
    } else {
      if ( (data[3].fvalue < (float)1.6507599354)) {
        sum += (float)-0.0099828979;
      } else {
        sum += (float)0.013825667091;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.65716946125)) {
      if ( (data[2].fvalue < (float)0.2107155025)) {
        sum += (float)-0.053903311491;
      } else {
        sum += (float)-0.01222932525;
      }
    } else {
      if ( (data[3].fvalue < (float)0.85539448261)) {
        sum += (float)0.022543383762;
      } else {
        sum += (float)-0.0029736580327;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.6939299107)) {
    if ( (data[3].fvalue < (float)2.1001698971)) {
      if ( (data[3].fvalue < (float)1.0616149902)) {
        sum += (float)0.0063680657186;
      } else {
        sum += (float)-0.0059433388524;
      }
    } else {
      if ( (data[0].fvalue < (float)285.45849609)) {
        sum += (float)-0.022293640301;
      } else {
        sum += (float)0.019021561369;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)512.63146973)) {
      if ( (data[0].fvalue < (float)151.93148804)) {
        sum += (float)0.011525295675;
      } else {
        sum += (float)-0.036901094019;
      }
    } else {
      if ( (data[2].fvalue < (float)2.697355032)) {
        sum += (float)-0.09098239243;
      } else {
        sum += (float)-0.0009163293289;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.31984299421)) {
    if ( (data[2].fvalue < (float)0.15581950545)) {
      if ( (data[1].fvalue < (float)21.309398651)) {
        sum += (float)-0.065339885652;
      } else {
        sum += (float)0.061369806528;
      }
    } else {
      if ( (data[0].fvalue < (float)333.70147705)) {
        sum += (float)-0.050701517612;
      } else {
        sum += (float)-0.0084809353575;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.69352900982)) {
      if ( (data[0].fvalue < (float)171.32400513)) {
        sum += (float)-0.035233255476;
      } else {
        sum += (float)0.021127453074;
      }
    } else {
      if ( (data[0].fvalue < (float)377.54699707)) {
        sum += (float)-0.0064568831585;
      } else {
        sum += (float)0.0029265189078;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.65320646763)) {
    if ( (data[3].fvalue < (float)0.39540249109)) {
      if ( (data[2].fvalue < (float)0.2026244998)) {
        sum += (float)-0.043591435999;
      } else {
        sum += (float)0.0093834092841;
      }
    } else {
      if ( (data[0].fvalue < (float)287.86099243)) {
        sum += (float)-0.038213025779;
      } else {
        sum += (float)-0.011638977565;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.93151652813)) {
      if ( (data[0].fvalue < (float)186.60449219)) {
        sum += (float)-0.032540649176;
      } else {
        sum += (float)0.024572333321;
      }
    } else {
      if ( (data[0].fvalue < (float)393.73248291)) {
        sum += (float)-0.0058465376496;
      } else {
        sum += (float)0.0029274981935;
      }
    }
  }
  if ( (data[1].fvalue < (float)1.5106250048)) {
    if ( (data[3].fvalue < (float)1.4890400171)) {
      if ( (data[2].fvalue < (float)0.91598600149)) {
        sum += (float)0.0082977097481;
      } else {
        sum += (float)0.032966576517;
      }
    } else {
      if ( (data[3].fvalue < (float)1.6507599354)) {
        sum += (float)-0.022323263809;
      } else {
        sum += (float)0.012392267585;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)2.6548399925)) {
      if ( (data[3].fvalue < (float)2.093775034)) {
        sum += (float)-0.0030745496042;
      } else {
        sum += (float)0.0087810307741;
      }
    } else {
      if ( (data[0].fvalue < (float)464.84747314)) {
        sum += (float)-0.034953590482;
      } else {
        sum += (float)-0.0052586379461;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.29322505)) {
    if ( (data[3].fvalue < (float)2.1071350574)) {
      if ( (data[1].fvalue < (float)3.8642599583)) {
        sum += (float)0.0059347320348;
      } else {
        sum += (float)-0.0046888091601;
      }
    } else {
      if ( (data[0].fvalue < (float)294.2789917)) {
        sum += (float)-0.012334357016;
      } else {
        sum += (float)0.031110972166;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)430.57250977)) {
      if ( (data[2].fvalue < (float)2.8246150017)) {
        sum += (float)-0.014879303053;
      } else {
        sum += (float)-0.040807452053;
      }
    } else {
      if ( (data[3].fvalue < (float)2.5602750778)) {
        sum += (float)0.0045785144903;
      } else {
        sum += (float)-0.013200104237;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.5110899806)) {
    if ( (data[2].fvalue < (float)0.18280100822)) {
      if ( (data[0].fvalue < (float)126.97250366)) {
        sum += (float)0.0617608428;
      } else {
        sum += (float)-0.054579377174;
      }
    } else {
      if ( (data[0].fvalue < (float)289.35150146)) {
        sum += (float)-0.033390425146;
      } else {
        sum += (float)-0.0052021169104;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.69240951538)) {
      if ( (data[0].fvalue < (float)171.74899292)) {
        sum += (float)-0.032955035567;
      } else {
        sum += (float)0.025854045525;
      }
    } else {
      if ( (data[2].fvalue < (float)2.29322505)) {
        sum += (float)0.00072488281876;
      } else {
        sum += (float)-0.0091451434419;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.65320646763)) {
    if ( (data[3].fvalue < (float)0.39540249109)) {
      if ( (data[2].fvalue < (float)0.28924751282)) {
        sum += (float)-0.021006215364;
      } else {
        sum += (float)0.011220882647;
      }
    } else {
      if ( (data[0].fvalue < (float)287.86099243)) {
        sum += (float)-0.033691149205;
      } else {
        sum += (float)-0.0099704060704;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)1.0707349777)) {
      if ( (data[0].fvalue < (float)194.57449341)) {
        sum += (float)-0.027370462194;
      } else {
        sum += (float)0.018882660195;
      }
    } else {
      if ( (data[3].fvalue < (float)1.9984999895)) {
        sum += (float)-0.0052859210409;
      } else {
        sum += (float)0.0040611610748;
      }
    }
  }
  if ( (data[1].fvalue < (float)5.5621299744)) {
    if ( (data[3].fvalue < (float)1.2485049963)) {
      if ( (data[2].fvalue < (float)0.76895797253)) {
        sum += (float)-0.0042083389126;
      } else {
        sum += (float)0.021109966561;
      }
    } else {
      if ( (data[3].fvalue < (float)1.9480750561)) {
        sum += (float)-0.0042336150073;
      } else {
        sum += (float)0.0049529592507;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.41648048162)) {
      if ( (data[2].fvalue < (float)0.70151752234)) {
        sum += (float)0.003721826477;
      } else {
        sum += (float)0.032582182437;
      }
    } else {
      if ( (data[2].fvalue < (float)1.1280950308)) {
        sum += (float)-0.013092363253;
      } else {
        sum += (float)-0.0015698507195;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.2645950317)) {
    if ( (data[3].fvalue < (float)2.251240015)) {
      if ( (data[1].fvalue < (float)3.8652300835)) {
        sum += (float)0.0056166811846;
      } else {
        sum += (float)-0.0033651725389;
      }
    } else {
      if ( (data[0].fvalue < (float)254.95800781)) {
        sum += (float)-0.015725318342;
      } else {
        sum += (float)0.031634613872;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)302.88650513)) {
      if ( (data[3].fvalue < (float)1.6749550104)) {
        sum += (float)0.08688633889;
      } else {
        sum += (float)-0.023588767275;
      }
    } else {
      if ( (data[2].fvalue < (float)2.7574849129)) {
        sum += (float)-0.0011462523835;
      } else {
        sum += (float)-0.021845815703;
      }
    }
  }
  if ( (data[1].fvalue < (float)1.5106250048)) {
    if ( (data[3].fvalue < (float)1.4890400171)) {
      if ( (data[2].fvalue < (float)0.91598600149)) {
        sum += (float)0.006716275122;
      } else {
        sum += (float)0.028211245313;
      }
    } else {
      if ( (data[3].fvalue < (float)1.6192700863)) {
        sum += (float)-0.023551302031;
      } else {
        sum += (float)0.010008676909;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.23409549892)) {
      if ( (data[0].fvalue < (float)130.68699646)) {
        sum += (float)0.059948202223;
      } else {
        sum += (float)-0.041113507003;
      }
    } else {
      if ( (data[3].fvalue < (float)0.57775652409)) {
        sum += (float)0.012765306048;
      } else {
        sum += (float)-0.0019522061339;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.2645950317)) {
    if ( (data[3].fvalue < (float)2.2147250175)) {
      if ( (data[0].fvalue < (float)130.13848877)) {
        sum += (float)-0.019686905667;
      } else {
        sum += (float)0.00015614266158;
      }
    } else {
      if ( (data[0].fvalue < (float)254.95800781)) {
        sum += (float)-0.015323034488;
      } else {
        sum += (float)0.027457628399;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)305.81399536)) {
      if ( (data[3].fvalue < (float)1.6665049791)) {
        sum += (float)0.078842811286;
      } else {
        sum += (float)-0.021199779585;
      }
    } else {
      if ( (data[2].fvalue < (float)2.7577950954)) {
        sum += (float)-0.00091061118292;
      } else {
        sum += (float)-0.020015297458;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.2107155025)) {
    if ( (data[0].fvalue < (float)471.96398926)) {
      if ( (data[0].fvalue < (float)130.68699646)) {
        sum += (float)0.045396476984;
      } else {
        sum += (float)-0.058586049825;
      }
    } else {
      if ( (data[2].fvalue < (float)0.15259599686)) {
        sum += (float)-0.04536042735;
      } else {
        sum += (float)0.022423624992;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.78330552578)) {
      if ( (data[2].fvalue < (float)0.70003801584)) {
        sum += (float)-0.0016117092455;
      } else {
        sum += (float)0.019610634074;
      }
    } else {
      if ( (data[2].fvalue < (float)1.0676950216)) {
        sum += (float)-0.010471965186;
      } else {
        sum += (float)0.00051486951998;
      }
    }
  }
  if ( (data[1].fvalue < (float)1.7464849949)) {
    if ( (data[0].fvalue < (float)429.65249634)) {
      if ( (data[0].fvalue < (float)281.09899902)) {
        sum += (float)0.016789136454;
      } else {
        sum += (float)-0.0055703492835;
      }
    } else {
      if ( (data[2].fvalue < (float)1.7988100052)) {
        sum += (float)0.021279910579;
      } else {
        sum += (float)0.0065199411474;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.54987347126)) {
      if ( (data[0].fvalue < (float)42.034797668)) {
        sum += (float)0.11164402962;
      } else {
        sum += (float)-0.013233616948;
      }
    } else {
      if ( (data[3].fvalue < (float)0.576135993)) {
        sum += (float)0.019142169505;
      } else {
        sum += (float)-0.0013383461628;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.5850250721)) {
    if ( (data[3].fvalue < (float)2.2462849617)) {
      if ( (data[3].fvalue < (float)1.184210062)) {
        sum += (float)0.0037726599257;
      } else {
        sum += (float)-0.0036781062372;
      }
    } else {
      if ( (data[0].fvalue < (float)260.70349121)) {
        sum += (float)-0.016158584505;
      } else {
        sum += (float)0.015707537532;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)522.28955078)) {
      if ( (data[0].fvalue < (float)126.50749969)) {
        sum += (float)0.027789151296;
      } else {
        sum += (float)-0.022004451603;
      }
    } else {
      if ( (data[3].fvalue < (float)2.1582298279)) {
        sum += (float)0.040194518864;
      } else {
        sum += (float)0.001564511098;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.70146948099)) {
    if ( (data[3].fvalue < (float)0.39540600777)) {
      if ( (data[2].fvalue < (float)0.18115249276)) {
        sum += (float)-0.036600138992;
      } else {
        sum += (float)0.0075488048606;
      }
    } else {
      if ( (data[0].fvalue < (float)252.81600952)) {
        sum += (float)-0.032236643136;
      } else {
        sum += (float)-0.0074173114263;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)1.0553050041)) {
      if ( (data[0].fvalue < (float)194.57449341)) {
        sum += (float)-0.025523519143;
      } else {
        sum += (float)0.016630988568;
      }
    } else {
      if ( (data[3].fvalue < (float)1.9984999895)) {
        sum += (float)-0.0038295045961;
      } else {
        sum += (float)0.0031755331438;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.2483448982)) {
    if ( (data[3].fvalue < (float)2.1071350574)) {
      if ( (data[1].fvalue < (float)4.3033499718)) {
        sum += (float)0.0042588873766;
      } else {
        sum += (float)-0.0035515923519;
      }
    } else {
      if ( (data[0].fvalue < (float)294.26251221)) {
        sum += (float)-0.010547273792;
      } else {
        sum += (float)0.024054653943;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)430.42599487)) {
      if ( (data[2].fvalue < (float)2.8246150017)) {
        sum += (float)-0.010659924708;
      } else {
        sum += (float)-0.033549342304;
      }
    } else {
      if ( (data[3].fvalue < (float)2.5692548752)) {
        sum += (float)0.0043712267652;
      } else {
        sum += (float)-0.00923388917;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.2107155025)) {
    if ( (data[0].fvalue < (float)471.96398926)) {
      if ( (data[0].fvalue < (float)130.68699646)) {
        sum += (float)0.041951574385;
      } else {
        sum += (float)-0.053740333766;
      }
    } else {
      if ( (data[2].fvalue < (float)0.15259599686)) {
        sum += (float)-0.041218262166;
      } else {
        sum += (float)0.020860133693;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.5783405304)) {
      if ( (data[2].fvalue < (float)0.7763800025)) {
        sum += (float)0.0030056952965;
      } else {
        sum += (float)0.026054948568;
      }
    } else {
      if ( (data[2].fvalue < (float)0.87735801935)) {
        sum += (float)-0.0094294734299;
      } else {
        sum += (float)0.00057371426374;
      }
    }
  }
  if ( (data[1].fvalue < (float)1.2922999859)) {
    if ( (data[3].fvalue < (float)1.3324099779)) {
      if ( (data[2].fvalue < (float)1.1364450455)) {
        sum += (float)0.015020745806;
      } else {
        sum += (float)0.036041852087;
      }
    } else {
      if ( (data[0].fvalue < (float)487.68499756)) {
        sum += (float)-0.001293517882;
      } else {
        sum += (float)0.013749251142;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.46617150307)) {
      if ( (data[2].fvalue < (float)0.12679100037)) {
        sum += (float)-0.05809558183;
      } else {
        sum += (float)-0.010611311533;
      }
    } else {
      if ( (data[3].fvalue < (float)0.89037895203)) {
        sum += (float)0.0085609359667;
      } else {
        sum += (float)-0.0016818344593;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.247025013)) {
    if ( (data[3].fvalue < (float)2.2921550274)) {
      if ( (data[1].fvalue < (float)5.0600700378)) {
        sum += (float)0.0034224947449;
      } else {
        sum += (float)-0.0030525017064;
      }
    } else {
      if ( (data[1].fvalue < (float)11.134799957)) {
        sum += (float)0.023731375113;
      } else {
        sum += (float)-0.029710024595;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)305.81399536)) {
      if ( (data[3].fvalue < (float)1.6749550104)) {
        sum += (float)0.069568827748;
      } else {
        sum += (float)-0.018684573472;
      }
    } else {
      if ( (data[2].fvalue < (float)2.7577950954)) {
        sum += (float)-0.00056203844724;
      } else {
        sum += (float)-0.016451127827;
      }
    }
  }
  if ( (data[0].fvalue < (float)130.13949585)) {
    if ( (data[2].fvalue < (float)2.3153848648)) {
      if ( (data[2].fvalue < (float)0.34270450473)) {
        sum += (float)0.053524594754;
      } else {
        sum += (float)-0.0186361745;
      }
    } else {
      if ( (data[3].fvalue < (float)2.2702100277)) {
        sum += (float)-0.022950503975;
      } else {
        sum += (float)0.035965736955;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)2.461810112)) {
      if ( (data[3].fvalue < (float)2.248374939)) {
        sum += (float)-8.3757462562e-05;
      } else {
        sum += (float)0.012227470987;
      }
    } else {
      if ( (data[3].fvalue < (float)2.5008349419)) {
        sum += (float)0.0014042825205;
      } else {
        sum += (float)-0.020975865424;
      }
    }
  }
  if ( (data[1].fvalue < (float)1.5107550621)) {
    if ( (data[3].fvalue < (float)1.4890400171)) {
      if ( (data[2].fvalue < (float)1.0590949059)) {
        sum += (float)0.005793585442;
      } else {
        sum += (float)0.024725085124;
      }
    } else {
      if ( (data[3].fvalue < (float)1.6507599354)) {
        sum += (float)-0.01979063265;
      } else {
        sum += (float)0.0079881222919;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)561.68499756)) {
      if ( (data[2].fvalue < (float)2.5276250839)) {
        sum += (float)0.00076094549149;
      } else {
        sum += (float)-0.012288151309;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8484100103)) {
        sum += (float)-0.018437303603;
      } else {
        sum += (float)0.0072091356851;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.18280100822)) {
    if ( (data[0].fvalue < (float)166.30300903)) {
      if ( (data[0].fvalue < (float)37.286697388)) {
        sum += (float)-0.073207974434;
      } else {
        sum += (float)0.056618250906;
      }
    } else {
      if ( (data[0].fvalue < (float)402.20898438)) {
        sum += (float)-0.066590093076;
      } else {
        sum += (float)-0.019627438858;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.76834952831)) {
      if ( (data[0].fvalue < (float)205.89498901)) {
        sum += (float)-0.017642745748;
      } else {
        sum += (float)0.0099870758131;
      }
    } else {
      if ( (data[2].fvalue < (float)1.0707149506)) {
        sum += (float)-0.0083819758147;
      } else {
        sum += (float)0.00063319655601;
      }
    }
  }
  if ( (data[1].fvalue < (float)6.3147850037)) {
    if ( (data[3].fvalue < (float)1.2609950304)) {
      if ( (data[2].fvalue < (float)0.77074599266)) {
        sum += (float)-0.0033422836568;
      } else {
        sum += (float)0.015366978012;
      }
    } else {
      if ( (data[3].fvalue < (float)1.9480750561)) {
        sum += (float)-0.0047620232217;
      } else {
        sum += (float)0.0035090558231;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.97920799255)) {
      if ( (data[3].fvalue < (float)0.64099097252)) {
        sum += (float)0.0014475919306;
      } else {
        sum += (float)-0.016026722267;
      }
    } else {
      if ( (data[3].fvalue < (float)1.634739995)) {
        sum += (float)0.0028489315882;
      } else {
        sum += (float)-0.0038706788328;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.247025013)) {
    if ( (data[3].fvalue < (float)2.1071350574)) {
      if ( (data[3].fvalue < (float)1.1875400543)) {
        sum += (float)0.002993834205;
      } else {
        sum += (float)-0.0030898151454;
      }
    } else {
      if ( (data[0].fvalue < (float)294.25100708)) {
        sum += (float)-0.010309598409;
      } else {
        sum += (float)0.019666530192;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)305.81399536)) {
      if ( (data[3].fvalue < (float)1.6749550104)) {
        sum += (float)0.060865618289;
      } else {
        sum += (float)-0.01684034057;
      }
    } else {
      if ( (data[3].fvalue < (float)2.569849968)) {
        sum += (float)0.00097058241954;
      } else {
        sum += (float)-0.0091090714559;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.31984299421)) {
    if ( (data[0].fvalue < (float)331.23449707)) {
      if ( (data[0].fvalue < (float)169.61499023)) {
        sum += (float)0.022833876312;
      } else {
        sum += (float)-0.05297280103;
      }
    } else {
      if ( (data[2].fvalue < (float)0.13034850359)) {
        sum += (float)-0.044581215829;
      } else {
        sum += (float)-0.0025165358093;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.57775652409)) {
      if ( (data[0].fvalue < (float)170.00050354)) {
        sum += (float)-0.026418089867;
      } else {
        sum += (float)0.012625016272;
      }
    } else {
      if ( (data[2].fvalue < (float)1.0710549355)) {
        sum += (float)-0.0056823887862;
      } else {
        sum += (float)0.0008855193737;
      }
    }
  }
  if ( (data[1].fvalue < (float)2.8075249195)) {
    if ( (data[3].fvalue < (float)1.152125001)) {
      if ( (data[2].fvalue < (float)0.77074599266)) {
        sum += (float)0.0017158791889;
      } else {
        sum += (float)0.026161501184;
      }
    } else {
      if ( (data[0].fvalue < (float)554.62646484)) {
        sum += (float)-0.0010391696123;
      } else {
        sum += (float)0.010859535076;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)561.68499756)) {
      if ( (data[2].fvalue < (float)2.6547551155)) {
        sum += (float)0.00036741161603;
      } else {
        sum += (float)-0.015834877267;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8545449972)) {
        sum += (float)-0.023438138887;
      } else {
        sum += (float)0.0045995921828;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.4575740099)) {
    if ( (data[0].fvalue < (float)309.82098389)) {
      if ( (data[0].fvalue < (float)43.058952332)) {
        sum += (float)0.093822188675;
      } else {
        sum += (float)-0.0290580336;
      }
    } else {
      if ( (data[2].fvalue < (float)0.15259599686)) {
        sum += (float)-0.038551915437;
      } else {
        sum += (float)-0.0015195718734;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.89037895203)) {
      if ( (data[0].fvalue < (float)205.89599609)) {
        sum += (float)-0.020739123225;
      } else {
        sum += (float)0.011933842674;
      }
    } else {
      if ( (data[2].fvalue < (float)1.2519049644)) {
        sum += (float)-0.0057468237355;
      } else {
        sum += (float)0.00058756541694;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.197124958)) {
    if ( (data[3].fvalue < (float)2.1071350574)) {
      if ( (data[1].fvalue < (float)5.0600700378)) {
        sum += (float)0.0029263056349;
      } else {
        sum += (float)-0.003058967879;
      }
    } else {
      if ( (data[0].fvalue < (float)315.68548584)) {
        sum += (float)-0.0054869269952;
      } else {
        sum += (float)0.019742405042;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)285.59100342)) {
      if ( (data[3].fvalue < (float)1.6397049427)) {
        sum += (float)0.076239489019;
      } else {
        sum += (float)-0.017408886924;
      }
    } else {
      if ( (data[2].fvalue < (float)2.9114699364)) {
        sum += (float)-0.00094604864717;
      } else {
        sum += (float)-0.021821629256;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.81400901079)) {
    if ( (data[3].fvalue < (float)0.28836548328)) {
      if ( (data[0].fvalue < (float)339.34799194)) {
        sum += (float)0.028429154307;
      } else {
        sum += (float)0.00029068469303;
      }
    } else {
      if ( (data[0].fvalue < (float)230.2164917)) {
        sum += (float)-0.024599308148;
      } else {
        sum += (float)-0.0040920674801;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)1.1014499664)) {
      if ( (data[0].fvalue < (float)205.89599609)) {
        sum += (float)-0.01990005374;
      } else {
        sum += (float)0.014471188188;
      }
    } else {
      if ( (data[0].fvalue < (float)397.35949707)) {
        sum += (float)-0.0033161889296;
      } else {
        sum += (float)0.0015118862502;
      }
    }
  }
  if ( (data[1].fvalue < (float)1.2922999859)) {
    if ( (data[0].fvalue < (float)487.68499756)) {
      if ( (data[0].fvalue < (float)282.85848999)) {
        sum += (float)0.01973747462;
      } else {
        sum += (float)-0.0013847718947;
      }
    } else {
      if ( (data[2].fvalue < (float)1.7988100052)) {
        sum += (float)0.024883320555;
      } else {
        sum += (float)0.002510975115;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)534.16247559)) {
      if ( (data[2].fvalue < (float)2.2452549934)) {
        sum += (float)0.0016208054731;
      } else {
        sum += (float)-0.0059078363702;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8775500059)) {
        sum += (float)-0.013065702282;
      } else {
        sum += (float)0.0064548566006;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.62268650532)) {
    if ( (data[0].fvalue < (float)47.926250458)) {
      if ( (data[1].fvalue < (float)22.405099869)) {
        sum += (float)0.24203431606;
      } else {
        sum += (float)0.044874861836;
      }
    } else {
      if ( (data[0].fvalue < (float)251.47351074)) {
        sum += (float)-0.024529477581;
      } else {
        sum += (float)-0.0033944051247;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)1.0231750011)) {
      if ( (data[0].fvalue < (float)194.57449341)) {
        sum += (float)-0.020942760631;
      } else {
        sum += (float)0.010760788806;
      }
    } else {
      if ( (data[2].fvalue < (float)1.2519049644)) {
        sum += (float)-0.0057913782075;
      } else {
        sum += (float)0.00029273907421;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.2107155025)) {
    if ( (data[0].fvalue < (float)471.96398926)) {
      if ( (data[0].fvalue < (float)185.68099976)) {
        sum += (float)0.019534574822;
      } else {
        sum += (float)-0.044901818037;
      }
    } else {
      if ( (data[2].fvalue < (float)0.15259599686)) {
        sum += (float)-0.028237685561;
      } else {
        sum += (float)0.021675324067;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.28218698502)) {
      if ( (data[0].fvalue < (float)339.34799194)) {
        sum += (float)0.03238510713;
      } else {
        sum += (float)0.0021314157639;
      }
    } else {
      if ( (data[2].fvalue < (float)0.87735801935)) {
        sum += (float)-0.0049090241082;
      } else {
        sum += (float)0.00075482780812;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.9212350845)) {
    if ( (data[1].fvalue < (float)6.3147850037)) {
      if ( (data[3].fvalue < (float)1.3476799726)) {
        sum += (float)0.0062100943178;
      } else {
        sum += (float)-0.00097575085238;
      }
    } else {
      if ( (data[0].fvalue < (float)540.50354004)) {
        sum += (float)-0.001436494058;
      } else {
        sum += (float)-0.018890580162;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)563.49749756)) {
      if ( (data[0].fvalue < (float)111.41600037)) {
        sum += (float)0.043188557029;
      } else {
        sum += (float)-0.031456485391;
      }
    } else {
      if ( (data[0].fvalue < (float)569.81896973)) {
        sum += (float)0.088043503463;
      } else {
        sum += (float)-0.0049225320108;
      }
    }
  }
  if ( (data[1].fvalue < (float)1.7464849949)) {
    if ( (data[0].fvalue < (float)429.65249634)) {
      if ( (data[0].fvalue < (float)281.09899902)) {
        sum += (float)0.01408048626;
      } else {
        sum += (float)-0.0069787926041;
      }
    } else {
      if ( (data[1].fvalue < (float)0.48836147785)) {
        sum += (float)-0.014440566301;
      } else {
        sum += (float)0.011607535183;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)561.68499756)) {
      if ( (data[2].fvalue < (float)2.5113699436)) {
        sum += (float)0.00068428338272;
      } else {
        sum += (float)-0.0087378537282;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8484100103)) {
        sum += (float)-0.015132521279;
      } else {
        sum += (float)0.0030163270421;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.36160099506)) {
    if ( (data[0].fvalue < (float)331.14849854)) {
      if ( (data[0].fvalue < (float)127.26100159)) {
        sum += (float)0.038896869868;
      } else {
        sum += (float)-0.039921265095;
      }
    } else {
      if ( (data[2].fvalue < (float)0.13034850359)) {
        sum += (float)-0.035938899964;
      } else {
        sum += (float)-0.00018103705952;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.69352900982)) {
      if ( (data[0].fvalue < (float)171.32400513)) {
        sum += (float)-0.021148992702;
      } else {
        sum += (float)0.0092074526474;
      }
    } else {
      if ( (data[2].fvalue < (float)1.1410150528)) {
        sum += (float)-0.0047339103185;
      } else {
        sum += (float)0.00070041423896;
      }
    }
  }
  if ( (data[1].fvalue < (float)6.931895256)) {
    if ( (data[3].fvalue < (float)1.3476799726)) {
      if ( (data[0].fvalue < (float)205.59649658)) {
        sum += (float)-0.02009389922;
      } else {
        sum += (float)0.0072033773176;
      }
    } else {
      if ( (data[3].fvalue < (float)1.9014550447)) {
        sum += (float)-0.0060207056813;
      } else {
        sum += (float)0.0031510279514;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)1.4383199215)) {
      if ( (data[1].fvalue < (float)11.713449478)) {
        sum += (float)-0.0026411414146;
      } else {
        sum += (float)-0.017276993021;
      }
    } else {
      if ( (data[3].fvalue < (float)1.6381850243)) {
        sum += (float)0.023564368486;
      } else {
        sum += (float)-0.0040670367889;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.81400901079)) {
    if ( (data[3].fvalue < (float)0.39538651705)) {
      if ( (data[0].fvalue < (float)361.87399292)) {
        sum += (float)0.015949120745;
      } else {
        sum += (float)-0.0028282606509;
      }
    } else {
      if ( (data[0].fvalue < (float)251.45100403)) {
        sum += (float)-0.019723512232;
      } else {
        sum += (float)-0.0036896930542;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)1.1353600025)) {
      if ( (data[0].fvalue < (float)185.37150574)) {
        sum += (float)-0.022777404636;
      } else {
        sum += (float)0.010974319652;
      }
    } else {
      if ( (data[0].fvalue < (float)214.87850952)) {
        sum += (float)0.0073679587804;
      } else {
        sum += (float)-0.0017509462778;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.1395850182)) {
    if ( (data[3].fvalue < (float)2.0078248978)) {
      if ( (data[0].fvalue < (float)294.38299561)) {
        sum += (float)0.0041054217145;
      } else {
        sum += (float)-0.0024044166785;
      }
    } else {
      if ( (data[0].fvalue < (float)305.45300293)) {
        sum += (float)-0.010038184933;
      } else {
        sum += (float)0.017763795331;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)393.73449707)) {
      if ( (data[3].fvalue < (float)1.6397049427)) {
        sum += (float)0.038717430085;
      } else {
        sum += (float)-0.0096565736458;
      }
    } else {
      if ( (data[1].fvalue < (float)0.49323049188)) {
        sum += (float)-0.047035109252;
      } else {
        sum += (float)0.0011824427638;
      }
    }
  }
  if ( (data[1].fvalue < (float)1.2922999859)) {
    if ( (data[2].fvalue < (float)1.7988100052)) {
      if ( (data[0].fvalue < (float)492.22399902)) {
        sum += (float)0.0037477144506;
      } else {
        sum += (float)0.022467765957;
      }
    } else {
      if ( (data[1].fvalue < (float)0.49323049188)) {
        sum += (float)-0.036477502435;
      } else {
        sum += (float)0.0031917230226;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)534.16247559)) {
      if ( (data[3].fvalue < (float)1.6235849857)) {
        sum += (float)0.0024732018355;
      } else {
        sum += (float)-0.0020210014191;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8676099777)) {
        sum += (float)-0.011114874855;
      } else {
        sum += (float)0.0050383480266;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.23408900201)) {
    if ( (data[0].fvalue < (float)432.73651123)) {
      if ( (data[0].fvalue < (float)207.62950134)) {
        sum += (float)0.024488653988;
      } else {
        sum += (float)-0.043949630111;
      }
    } else {
      if ( (data[2].fvalue < (float)0.12877799571)) {
        sum += (float)-0.02762482129;
      } else {
        sum += (float)0.005216488149;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)6.9257102013)) {
      if ( (data[3].fvalue < (float)1.3476799726)) {
        sum += (float)0.0053465184756;
      } else {
        sum += (float)-0.00098730821628;
      }
    } else {
      if ( (data[3].fvalue < (float)1.4632400274)) {
        sum += (float)-0.0060189734213;
      } else {
        sum += (float)0.0014212693786;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.65320646763)) {
    if ( (data[0].fvalue < (float)45.935852051)) {
      if ( (data[1].fvalue < (float)22.405099869)) {
        sum += (float)0.18428355455;
      } else {
        sum += (float)0.030504340306;
      }
    } else {
      if ( (data[0].fvalue < (float)238.91049194)) {
        sum += (float)-0.020201606676;
      } else {
        sum += (float)-0.0031108842231;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)1.0231750011)) {
      if ( (data[0].fvalue < (float)462.58151245)) {
        sum += (float)0.011024688371;
      } else {
        sum += (float)-0.007171147503;
      }
    } else {
      if ( (data[0].fvalue < (float)397.45599365)) {
        sum += (float)-0.0026776567101;
      } else {
        sum += (float)0.0016001424519;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.9114699364)) {
    if ( (data[3].fvalue < (float)2.0076351166)) {
      if ( (data[3].fvalue < (float)1.5671149492)) {
        sum += (float)0.0010546786943;
      } else {
        sum += (float)-0.0050178589299;
      }
    } else {
      if ( (data[0].fvalue < (float)293.79650879)) {
        sum += (float)-0.011168092489;
      } else {
        sum += (float)0.0071468935348;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)111.41600037)) {
      if ( (data[1].fvalue < (float)13.6854496)) {
        sum += (float)0.21489357948;
      } else {
        sum += (float)-0.023549940437;
      }
    } else {
      if ( (data[0].fvalue < (float)563.49749756)) {
        sum += (float)-0.027757598087;
      } else {
        sum += (float)0.0098070148379;
      }
    }
  }
  if ( (data[0].fvalue < (float)577.33251953)) {
    if ( (data[1].fvalue < (float)6.931895256)) {
      if ( (data[3].fvalue < (float)1.5085849762)) {
        sum += (float)0.0044091437012;
      } else {
        sum += (float)-0.00066505739233;
      }
    } else {
      if ( (data[3].fvalue < (float)1.4632400274)) {
        sum += (float)-0.00583822513;
      } else {
        sum += (float)0.0016562844394;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)3.419645071)) {
      if ( (data[0].fvalue < (float)577.69750977)) {
        sum += (float)-0.071352899075;
      } else {
        sum += (float)0.0077105569653;
      }
    } else {
      if ( (data[2].fvalue < (float)2.4698150158)) {
        sum += (float)-0.018890187144;
      } else {
        sum += (float)0.010826410726;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.92721748352)) {
    if ( (data[1].fvalue < (float)11.596250534)) {
      if ( (data[3].fvalue < (float)0.39020699263)) {
        sum += (float)0.0077271051705;
      } else {
        sum += (float)-0.0035909002181;
      }
    } else {
      if ( (data[0].fvalue < (float)74.580795288)) {
        sum += (float)0.014670251869;
      } else {
        sum += (float)-0.023314695805;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.93151652813)) {
      if ( (data[1].fvalue < (float)5.061249733)) {
        sum += (float)0.026212919503;
      } else {
        sum += (float)0.0024798708037;
      }
    } else {
      if ( (data[2].fvalue < (float)2.8031198978)) {
        sum += (float)0.00015856832033;
      } else {
        sum += (float)-0.011972631328;
      }
    }
  }
  if ( (data[1].fvalue < (float)35.07244873)) {
    if ( (data[0].fvalue < (float)42.546798706)) {
      if ( (data[1].fvalue < (float)8.2256250381)) {
        sum += (float)-0.0014592381194;
      } else {
        sum += (float)0.11526584625;
      }
    } else {
      if ( (data[0].fvalue < (float)111.36299896)) {
        sum += (float)-0.012819576077;
      } else {
        sum += (float)0.0002231587423;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)2.7545199394)) {
      if ( (data[1].fvalue < (float)35.65430069)) {
        sum += (float)-0.081090152264;
      } else {
        sum += (float)-0.01495579537;
      }
    } else {
      if ( (data[2].fvalue < (float)2.8806500435)) {
        sum += (float)0.12827931345;
      } else {
        sum += (float)-0.033292729408;
      }
    }
  }

  sum = sum + (float)(-0);
  if (!pred_margin) {
    return pred_transform(sum);
  } else {
    return sum;
  }
}
};
