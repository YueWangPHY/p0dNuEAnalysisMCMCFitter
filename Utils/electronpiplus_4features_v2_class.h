
#include "BDTClassifier.h"
#include "math.h"
class electronpiplus_4features_v2_class : public BDTClassifier {
 public :
 electronpiplus_4features_v2_class() : BDTClassifier(1.) {;}
  ~electronpiplus_4features_v2_class() {;}


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
  if ( (data[1].fvalue < (float)7.6842699051)) {
    if ( (data[1].fvalue < (float)3.773360014)) {
      if ( (data[2].fvalue < (float)2.524600029)) {
        sum += (float)0.084884926677;
      } else {
        sum += (float)-0.033417951316;
      }
    } else {
      if ( (data[2].fvalue < (float)2.515059948)) {
        sum += (float)-0.0085874563083;
      } else {
        sum += (float)-0.089085832238;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)13.386949539)) {
      if ( (data[0].fvalue < (float)144.79100037)) {
        sum += (float)-0.14203208685;
      } else {
        sum += (float)-0.078992575407;
      }
    } else {
      if ( (data[0].fvalue < (float)138.89700317)) {
        sum += (float)-0.18382488191;
      } else {
        sum += (float)-0.14151893556;
      }
    }
  }
  if ( (data[1].fvalue < (float)8.6994895935)) {
    if ( (data[1].fvalue < (float)4.1389799118)) {
      if ( (data[2].fvalue < (float)2.4749450684)) {
        sum += (float)0.072761647403;
      } else {
        sum += (float)-0.026351317763;
      }
    } else {
      if ( (data[0].fvalue < (float)150.26400757)) {
        sum += (float)-0.10729431361;
      } else {
        sum += (float)-0.018058279529;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)153.69699097)) {
      if ( (data[1].fvalue < (float)17.587348938)) {
        sum += (float)-0.1364722997;
      } else {
        sum += (float)-0.16763909161;
      }
    } else {
      if ( (data[1].fvalue < (float)11.832849503)) {
        sum += (float)-0.075058825314;
      } else {
        sum += (float)-0.11781299114;
      }
    }
  }
  if ( (data[1].fvalue < (float)7.2216653824)) {
    if ( (data[1].fvalue < (float)3.2520849705)) {
      if ( (data[2].fvalue < (float)2.5010299683)) {
        sum += (float)0.077841766179;
      } else {
        sum += (float)-0.018640823662;
      }
    } else {
      if ( (data[2].fvalue < (float)2.5152349472)) {
        sum += (float)0.0017820190405;
      } else {
        sum += (float)-0.07348869741;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)13.386949539)) {
      if ( (data[0].fvalue < (float)142.60400391)) {
        sum += (float)-0.11860688031;
      } else {
        sum += (float)-0.061364140362;
      }
    } else {
      if ( (data[0].fvalue < (float)124.10800171)) {
        sum += (float)-0.15561276674;
      } else {
        sum += (float)-0.11999695748;
      }
    }
  }
  if ( (data[1].fvalue < (float)8.6994895935)) {
    if ( (data[1].fvalue < (float)4.344810009)) {
      if ( (data[2].fvalue < (float)2.5246450901)) {
        sum += (float)0.057569075376;
      } else {
        sum += (float)-0.028870228678;
      }
    } else {
      if ( (data[0].fvalue < (float)150.2460022)) {
        sum += (float)-0.092878736556;
      } else {
        sum += (float)-0.01636030525;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)16.072050095)) {
      if ( (data[0].fvalue < (float)130.0249939)) {
        sum += (float)-0.12053526938;
      } else {
        sum += (float)-0.074133001268;
      }
    } else {
      if ( (data[0].fvalue < (float)119.52899933)) {
        sum += (float)-0.14648239315;
      } else {
        sum += (float)-0.1196064502;
      }
    }
  }
  if ( (data[1].fvalue < (float)8.3466749191)) {
    if ( (data[1].fvalue < (float)2.9716300964)) {
      if ( (data[2].fvalue < (float)2.5550551414)) {
        sum += (float)0.068815499544;
      } else {
        sum += (float)-0.018117493019;
      }
    } else {
      if ( (data[1].fvalue < (float)5.6258502007)) {
        sum += (float)0.010275613517;
      } else {
        sum += (float)-0.029628312215;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)145.36898804)) {
      if ( (data[1].fvalue < (float)19.877300262)) {
        sum += (float)-0.11140992492;
      } else {
        sum += (float)-0.13701525331;
      }
    } else {
      if ( (data[1].fvalue < (float)10.940099716)) {
        sum += (float)-0.048584040254;
      } else {
        sum += (float)-0.089219562709;
      }
    }
  }
  if ( (data[1].fvalue < (float)9.8037643433)) {
    if ( (data[1].fvalue < (float)4.9935250282)) {
      if ( (data[0].fvalue < (float)191.38949585)) {
        sum += (float)-0.051255743951;
      } else {
        sum += (float)0.042751234025;
      }
    } else {
      if ( (data[2].fvalue < (float)2.5661549568)) {
        sum += (float)-0.021074218675;
      } else {
        sum += (float)-0.084362313151;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)139.77400208)) {
      if ( (data[1].fvalue < (float)26.058050156)) {
        sum += (float)-0.11262100935;
      } else {
        sum += (float)-0.13230524957;
      }
    } else {
      if ( (data[1].fvalue < (float)13.406100273)) {
        sum += (float)-0.062872998416;
      } else {
        sum += (float)-0.092511542141;
      }
    }
  }
  if ( (data[1].fvalue < (float)9.4085655212)) {
    if ( (data[1].fvalue < (float)2.8120398521)) {
      if ( (data[2].fvalue < (float)2.3823199272)) {
        sum += (float)0.063932158053;
      } else {
        sum += (float)-0.0013349213405;
      }
    } else {
      if ( (data[0].fvalue < (float)150.26699829)) {
        sum += (float)-0.082012347877;
      } else {
        sum += (float)-0.005090188235;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)17.587551117)) {
      if ( (data[0].fvalue < (float)132.71949768)) {
        sum += (float)-0.099693372846;
      } else {
        sum += (float)-0.062155317515;
      }
    } else {
      if ( (data[0].fvalue < (float)114.41600037)) {
        sum += (float)-0.1250590086;
      } else {
        sum += (float)-0.1021238938;
      }
    }
  }
  if ( (data[1].fvalue < (float)10.105350494)) {
    if ( (data[1].fvalue < (float)3.773360014)) {
      if ( (data[0].fvalue < (float)258.78051758)) {
        sum += (float)-0.016165787354;
      } else {
        sum += (float)0.04881849885;
      }
    } else {
      if ( (data[2].fvalue < (float)2.5661549568)) {
        sum += (float)-0.010529253632;
      } else {
        sum += (float)-0.074019648135;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)139.75549316)) {
      if ( (data[1].fvalue < (float)26.750749588)) {
        sum += (float)-0.10054355115;
      } else {
        sum += (float)-0.12079328299;
      }
    } else {
      if ( (data[1].fvalue < (float)13.735599518)) {
        sum += (float)-0.054981917143;
      } else {
        sum += (float)-0.081125915051;
      }
    }
  }
  if ( (data[1].fvalue < (float)6.7157154083)) {
    if ( (data[1].fvalue < (float)2.2661550045)) {
      if ( (data[2].fvalue < (float)2.5723900795)) {
        sum += (float)0.061048567295;
      } else {
        sum += (float)-0.018613766879;
      }
    } else {
      if ( (data[0].fvalue < (float)140.84249878)) {
        sum += (float)-0.080037780106;
      } else {
        sum += (float)0.0091610178351;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)166.20748901)) {
      if ( (data[0].fvalue < (float)103.78800201)) {
        sum += (float)-0.11219719797;
      } else {
        sum += (float)-0.079946935177;
      }
    } else {
      if ( (data[1].fvalue < (float)10.565349579)) {
        sum += (float)-0.028411304578;
      } else {
        sum += (float)-0.060141619295;
      }
    }
  }
  if ( (data[1].fvalue < (float)10.434599876)) {
    if ( (data[1].fvalue < (float)5.243350029)) {
      if ( (data[2].fvalue < (float)2.4954800606)) {
        sum += (float)0.031957454979;
      } else {
        sum += (float)-0.034968584776;
      }
    } else {
      if ( (data[0].fvalue < (float)106.48699951)) {
        sum += (float)-0.091808736324;
      } else {
        sum += (float)-0.019204771146;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)123.95500183)) {
      if ( (data[1].fvalue < (float)22.195049286)) {
        sum += (float)-0.090449988842;
      } else {
        sum += (float)-0.11111648381;
      }
    } else {
      if ( (data[1].fvalue < (float)16.239898682)) {
        sum += (float)-0.051393356174;
      } else {
        sum += (float)-0.080802790821;
      }
    }
  }
  if ( (data[0].fvalue < (float)219.65701294)) {
    if ( (data[0].fvalue < (float)114.12350464)) {
      if ( (data[1].fvalue < (float)20.764200211)) {
        sum += (float)-0.086631655693;
      } else {
        sum += (float)-0.10736658424;
      }
    } else {
      if ( (data[1].fvalue < (float)11.804849625)) {
        sum += (float)-0.029407009482;
      } else {
        sum += (float)-0.071571625769;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)5.7591400146)) {
      if ( (data[2].fvalue < (float)2.568655014)) {
        sum += (float)0.032439690083;
      } else {
        sum += (float)-0.035976763815;
      }
    } else {
      if ( (data[2].fvalue < (float)2.5795400143)) {
        sum += (float)-0.019171498716;
      } else {
        sum += (float)-0.06637596339;
      }
    }
  }
  if ( (data[1].fvalue < (float)10.891649246)) {
    if ( (data[1].fvalue < (float)2.3960599899)) {
      if ( (data[3].fvalue < (float)1.3288650513)) {
        sum += (float)0.070867620409;
      } else {
        sum += (float)0.027560641989;
      }
    } else {
      if ( (data[2].fvalue < (float)0.33612349629)) {
        sum += (float)-0.096581503749;
      } else {
        sum += (float)-0.005424042698;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)123.95500183)) {
      if ( (data[1].fvalue < (float)22.195049286)) {
        sum += (float)-0.081637851894;
      } else {
        sum += (float)-0.10331695527;
      }
    } else {
      if ( (data[1].fvalue < (float)16.770450592)) {
        sum += (float)-0.046360384673;
      } else {
        sum += (float)-0.072828099132;
      }
    }
  }
  if ( (data[0].fvalue < (float)192.42250061)) {
    if ( (data[0].fvalue < (float)109.65350342)) {
      if ( (data[1].fvalue < (float)33.929298401)) {
        sum += (float)-0.085062600672;
      } else {
        sum += (float)-0.1036766693;
      }
    } else {
      if ( (data[3].fvalue < (float)0.99187248945)) {
        sum += (float)-0.011623904109;
      } else {
        sum += (float)-0.059803228825;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)6.0014247894)) {
      if ( (data[2].fvalue < (float)2.5640599728)) {
        sum += (float)0.026694152504;
      } else {
        sum += (float)-0.034789003432;
      }
    } else {
      if ( (data[2].fvalue < (float)2.5985298157)) {
        sum += (float)-0.01959903352;
      } else {
        sum += (float)-0.065907619894;
      }
    }
  }
  if ( (data[1].fvalue < (float)10.560199738)) {
    if ( (data[1].fvalue < (float)2.8120398521)) {
      if ( (data[2].fvalue < (float)0.2720285058)) {
        sum += (float)-0.10690146685;
      } else {
        sum += (float)0.036567207426;
      }
    } else {
      if ( (data[2].fvalue < (float)2.4707250595)) {
        sum += (float)-0.002751901513;
      } else {
        sum += (float)-0.047237105668;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)19.907249451)) {
      if ( (data[0].fvalue < (float)104.66749573)) {
        sum += (float)-0.076679490507;
      } else {
        sum += (float)-0.042745478451;
      }
    } else {
      if ( (data[0].fvalue < (float)98.114105225)) {
        sum += (float)-0.09792984277;
      } else {
        sum += (float)-0.077326796949;
      }
    }
  }
  if ( (data[0].fvalue < (float)174.95899963)) {
    if ( (data[0].fvalue < (float)99.137054443)) {
      if ( (data[1].fvalue < (float)33.143997192)) {
        sum += (float)-0.08085861057;
      } else {
        sum += (float)-0.097708500922;
      }
    } else {
      if ( (data[3].fvalue < (float)0.99187248945)) {
        sum += (float)-0.014572677203;
      } else {
        sum += (float)-0.058588325977;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)5.5716953278)) {
      if ( (data[3].fvalue < (float)1.2119150162)) {
        sum += (float)0.045108865947;
      } else {
        sum += (float)0.0077948868275;
      }
    } else {
      if ( (data[2].fvalue < (float)0.33076000214)) {
        sum += (float)-0.08412938565;
      } else {
        sum += (float)-0.01666512154;
      }
    }
  }
  if ( (data[0].fvalue < (float)219.65701294)) {
    if ( (data[0].fvalue < (float)109.65350342)) {
      if ( (data[1].fvalue < (float)21.424249649)) {
        sum += (float)-0.068930521607;
      } else {
        sum += (float)-0.09113099426;
      }
    } else {
      if ( (data[3].fvalue < (float)1.1029649973)) {
        sum += (float)-0.0079555464908;
      } else {
        sum += (float)-0.046835530549;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)3.414080143)) {
      if ( (data[3].fvalue < (float)1.2119150162)) {
        sum += (float)0.056488335133;
      } else {
        sum += (float)0.017871890217;
      }
    } else {
      if ( (data[2].fvalue < (float)0.33463901281)) {
        sum += (float)-0.081289388239;
      } else {
        sum += (float)-0.0045331921428;
      }
    }
  }
  if ( (data[1].fvalue < (float)12.975349426)) {
    if ( (data[1].fvalue < (float)1.8537800312)) {
      if ( (data[3].fvalue < (float)1.4288250208)) {
        sum += (float)0.062138270587;
      } else {
        sum += (float)0.024744348601;
      }
    } else {
      if ( (data[2].fvalue < (float)0.33612349629)) {
        sum += (float)-0.082447320223;
      } else {
        sum += (float)-0.0031975456513;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)21.432498932)) {
      if ( (data[3].fvalue < (float)0.85699951649)) {
        sum += (float)-0.023037446663;
      } else {
        sum += (float)-0.053827524185;
      }
    } else {
      if ( (data[1].fvalue < (float)33.931049347)) {
        sum += (float)-0.073913805187;
      } else {
        sum += (float)-0.091916047037;
      }
    }
  }
  if ( (data[0].fvalue < (float)145.19049072)) {
    if ( (data[0].fvalue < (float)98.04045105)) {
      if ( (data[1].fvalue < (float)33.143997192)) {
        sum += (float)-0.070925340056;
      } else {
        sum += (float)-0.089394830167;
      }
    } else {
      if ( (data[3].fvalue < (float)0.82156801224)) {
        sum += (float)-0.0087632499635;
      } else {
        sum += (float)-0.054458480328;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)6.4500098228)) {
      if ( (data[2].fvalue < (float)0.38277298212)) {
        sum += (float)-0.065679311752;
      } else {
        sum += (float)0.016421673819;
      }
    } else {
      if ( (data[3].fvalue < (float)0.94667100906)) {
        sum += (float)0.0020961312111;
      } else {
        sum += (float)-0.026646995917;
      }
    }
  }
  if ( (data[1].fvalue < (float)12.368749619)) {
    if ( (data[1].fvalue < (float)1.763479948)) {
      if ( (data[3].fvalue < (float)1.427670002)) {
        sum += (float)0.058259870857;
      } else {
        sum += (float)0.022568695247;
      }
    } else {
      if ( (data[3].fvalue < (float)1.1281099319)) {
        sum += (float)0.017010804266;
      } else {
        sum += (float)-0.012110612355;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)21.432498932)) {
      if ( (data[3].fvalue < (float)0.99185144901)) {
        sum += (float)-0.022507192567;
      } else {
        sum += (float)-0.04635014385;
      }
    } else {
      if ( (data[1].fvalue < (float)33.931049347)) {
        sum += (float)-0.067741759121;
      } else {
        sum += (float)-0.086410336196;
      }
    }
  }
  if ( (data[0].fvalue < (float)145.19049072)) {
    if ( (data[0].fvalue < (float)81.417098999)) {
      if ( (data[1].fvalue < (float)33.929298401)) {
        sum += (float)-0.070500545204;
      } else {
        sum += (float)-0.084814958274;
      }
    } else {
      if ( (data[1].fvalue < (float)15.118499756)) {
        sum += (float)-0.030442005023;
      } else {
        sum += (float)-0.061445821077;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)6.7327852249)) {
      if ( (data[2].fvalue < (float)2.3993051052)) {
        sum += (float)0.016731129959;
      } else {
        sum += (float)-0.02435609512;
      }
    } else {
      if ( (data[2].fvalue < (float)2.5985298157)) {
        sum += (float)-0.015921110287;
      } else {
        sum += (float)-0.057694870979;
      }
    }
  }
  if ( (data[0].fvalue < (float)252.43450928)) {
    if ( (data[0].fvalue < (float)101.98550415)) {
      if ( (data[1].fvalue < (float)33.143997192)) {
        sum += (float)-0.060245204717;
      } else {
        sum += (float)-0.081121318042;
      }
    } else {
      if ( (data[3].fvalue < (float)1.1026449203)) {
        sum += (float)-0.00087154482026;
      } else {
        sum += (float)-0.033691853285;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)3.2522950172)) {
      if ( (data[2].fvalue < (float)0.38424301147)) {
        sum += (float)-0.063630014658;
      } else {
        sum += (float)0.028683716431;
      }
    } else {
      if ( (data[2].fvalue < (float)2.5986149311)) {
        sum += (float)0.00045424583368;
      } else {
        sum += (float)-0.040414750576;
      }
    }
  }
  if ( (data[1].fvalue < (float)13.386949539)) {
    if ( (data[2].fvalue < (float)0.3286960125)) {
      if ( (data[2].fvalue < (float)0.2030300051)) {
        sum += (float)-0.10727119446;
      } else {
        sum += (float)-0.049902107567;
      }
    } else {
      if ( (data[3].fvalue < (float)1.0655750036)) {
        sum += (float)0.03021274507;
      } else {
        sum += (float)-0.0061090495437;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)26.750749588)) {
      if ( (data[0].fvalue < (float)173.93450928)) {
        sum += (float)-0.047817271203;
      } else {
        sum += (float)-0.029573205858;
      }
    } else {
      if ( (data[1].fvalue < (float)44.404800415)) {
        sum += (float)-0.06823977083;
      } else {
        sum += (float)-0.080710813403;
      }
    }
  }
  if ( (data[0].fvalue < (float)141.62799072)) {
    if ( (data[0].fvalue < (float)81.417098999)) {
      if ( (data[1].fvalue < (float)33.929298401)) {
        sum += (float)-0.061854101717;
      } else {
        sum += (float)-0.076799117029;
      }
    } else {
      if ( (data[1].fvalue < (float)15.739150047)) {
        sum += (float)-0.025717949495;
      } else {
        sum += (float)-0.054131682962;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)6.2384548187)) {
      if ( (data[2].fvalue < (float)0.43287450075)) {
        sum += (float)-0.049340851605;
      } else {
        sum += (float)0.013574707322;
      }
    } else {
      if ( (data[3].fvalue < (float)1.9689700603)) {
        sum += (float)-0.020982014015;
      } else {
        sum += (float)0.0018970918609;
      }
    }
  }
  if ( (data[0].fvalue < (float)258.77850342)) {
    if ( (data[0].fvalue < (float)98.04045105)) {
      if ( (data[1].fvalue < (float)33.929298401)) {
        sum += (float)-0.053477592766;
      } else {
        sum += (float)-0.07337731123;
      }
    } else {
      if ( (data[2].fvalue < (float)2.5010049343)) {
        sum += (float)-0.015666890889;
      } else {
        sum += (float)-0.062437761575;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)1.643830061)) {
      if ( (data[2].fvalue < (float)2.2434248924)) {
        sum += (float)0.045152883977;
      } else {
        sum += (float)0.0030268821865;
      }
    } else {
      if ( (data[2].fvalue < (float)2.6235499382)) {
        sum += (float)0.0038240861613;
      } else {
        sum += (float)-0.038146976382;
      }
    }
  }
  if ( (data[1].fvalue < (float)14.20775032)) {
    if ( (data[3].fvalue < (float)1.128880024)) {
      if ( (data[2].fvalue < (float)0.46597898006)) {
        sum += (float)-0.040447168052;
      } else {
        sum += (float)0.03037497215;
      }
    } else {
      if ( (data[3].fvalue < (float)1.9192299843)) {
        sum += (float)-0.016919590533;
      } else {
        sum += (float)0.0057952399366;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)26.938301086)) {
      if ( (data[3].fvalue < (float)0.89383494854)) {
        sum += (float)-0.016777914017;
      } else {
        sum += (float)-0.039907392114;
      }
    } else {
      if ( (data[1].fvalue < (float)64.983100891)) {
        sum += (float)-0.062138289213;
      } else {
        sum += (float)-0.076438687742;
      }
    }
  }
  if ( (data[1].fvalue < (float)8.6994895935)) {
    if ( (data[2].fvalue < (float)2.6466200352)) {
      if ( (data[2].fvalue < (float)0.27308049798)) {
        sum += (float)-0.072756096721;
      } else {
        sum += (float)0.0084694940597;
      }
    } else {
      if ( (data[0].fvalue < (float)345.11248779)) {
        sum += (float)-0.059617895633;
      } else {
        sum += (float)-0.029127834365;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)19.907249451)) {
      if ( (data[2].fvalue < (float)2.5341200829)) {
        sum += (float)-0.016174957156;
      } else {
        sum += (float)-0.0517167449;
      }
    } else {
      if ( (data[1].fvalue < (float)33.931049347)) {
        sum += (float)-0.046985059977;
      } else {
        sum += (float)-0.067406252027;
      }
    }
  }
  if ( (data[0].fvalue < (float)121.36750031)) {
    if ( (data[0].fvalue < (float)81.292098999)) {
      if ( (data[3].fvalue < (float)1.1259299517)) {
        sum += (float)-0.070484563708;
      } else {
        sum += (float)-0.054810862988;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8037600517)) {
        sum += (float)-0.022323971614;
      } else {
        sum += (float)-0.059009570628;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)4.5901699066)) {
      if ( (data[3].fvalue < (float)1.2083499432)) {
        sum += (float)0.033672053367;
      } else {
        sum += (float)0.0033450785559;
      }
    } else {
      if ( (data[2].fvalue < (float)2.5649299622)) {
        sum += (float)-0.0059407651424;
      } else {
        sum += (float)-0.039680343121;
      }
    }
  }
  if ( (data[0].fvalue < (float)258.77850342)) {
    if ( (data[0].fvalue < (float)98.04045105)) {
      if ( (data[1].fvalue < (float)33.929298401)) {
        sum += (float)-0.044146224856;
      } else {
        sum += (float)-0.062618762255;
      }
    } else {
      if ( (data[3].fvalue < (float)0.94239199162)) {
        sum += (float)0.0078722089529;
      } else {
        sum += (float)-0.022237053141;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)2.059235096)) {
      if ( (data[3].fvalue < (float)1.3757849932)) {
        sum += (float)0.047194078565;
      } else {
        sum += (float)0.016047213227;
      }
    } else {
      if ( (data[3].fvalue < (float)1.9753149748)) {
        sum += (float)-0.0056626256555;
      } else {
        sum += (float)0.013473704457;
      }
    }
  }
  if ( (data[1].fvalue < (float)8.2406902313)) {
    if ( (data[3].fvalue < (float)1.1853449345)) {
      if ( (data[2].fvalue < (float)0.49340599775)) {
        sum += (float)-0.032906077802;
      } else {
        sum += (float)0.032113134861;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8711249828)) {
        sum += (float)-0.013799759559;
      } else {
        sum += (float)0.0075110769831;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)17.587551117)) {
      if ( (data[2].fvalue < (float)0.33023300767)) {
        sum += (float)-0.065882906318;
      } else {
        sum += (float)-0.01229892578;
      }
    } else {
      if ( (data[1].fvalue < (float)26.938301086)) {
        sum += (float)-0.034848757088;
      } else {
        sum += (float)-0.055879879743;
      }
    }
  }
  if ( (data[0].fvalue < (float)121.36750031)) {
    if ( (data[0].fvalue < (float)74.70765686)) {
      if ( (data[2].fvalue < (float)1.5322250128)) {
        sum += (float)-0.061157103628;
      } else {
        sum += (float)-0.044771853834;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8071299791)) {
        sum += (float)-0.01901733689;
      } else {
        sum += (float)-0.051304724067;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)2.5268650055)) {
      if ( (data[3].fvalue < (float)1.9931800365)) {
        sum += (float)-0.0029781362973;
      } else {
        sum += (float)0.023111676797;
      }
    } else {
      if ( (data[0].fvalue < (float)307.39898682)) {
        sum += (float)-0.047991018742;
      } else {
        sum += (float)-0.021164564416;
      }
    }
  }
  if ( (data[0].fvalue < (float)300.71749878)) {
    if ( (data[1].fvalue < (float)17.587551117)) {
      if ( (data[2].fvalue < (float)2.4199099541)) {
        sum += (float)-0.0065814810805;
      } else {
        sum += (float)-0.040145348758;
      }
    } else {
      if ( (data[1].fvalue < (float)26.938301086)) {
        sum += (float)-0.031298756599;
      } else {
        sum += (float)-0.050671447068;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)1.515515089)) {
      if ( (data[2].fvalue < (float)2.645565033)) {
        sum += (float)0.037695702165;
      } else {
        sum += (float)-0.0164329689;
      }
    } else {
      if ( (data[3].fvalue < (float)1.0742750168)) {
        sum += (float)0.016378918663;
      } else {
        sum += (float)-0.0031988758128;
      }
    }
  }
  if ( (data[1].fvalue < (float)6.8469848633)) {
    if ( (data[2].fvalue < (float)0.2624605)) {
      if ( (data[2].fvalue < (float)0.1791664958)) {
        sum += (float)-0.097025260329;
      } else {
        sum += (float)-0.049497742206;
      }
    } else {
      if ( (data[3].fvalue < (float)1.1854050159)) {
        sum += (float)0.02523429133;
      } else {
        sum += (float)-0.0010613900376;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)19.907249451)) {
      if ( (data[3].fvalue < (float)1.9740450382)) {
        sum += (float)-0.015317014419;
      } else {
        sum += (float)0.0020072632469;
      }
    } else {
      if ( (data[1].fvalue < (float)44.404800415)) {
        sum += (float)-0.035458069295;
      } else {
        sum += (float)-0.054933231324;
      }
    }
  }
  if ( (data[0].fvalue < (float)139.75201416)) {
    if ( (data[0].fvalue < (float)81.292098999)) {
      if ( (data[3].fvalue < (float)1.1259299517)) {
        sum += (float)-0.057765226811;
      } else {
        sum += (float)-0.039001312107;
      }
    } else {
      if ( (data[3].fvalue < (float)0.73322403431)) {
        sum += (float)0.012562430464;
      } else {
        sum += (float)-0.02630546689;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.33119851351)) {
      if ( (data[2].fvalue < (float)0.2030300051)) {
        sum += (float)-0.081568956375;
      } else {
        sum += (float)-0.033983767033;
      }
    } else {
      if ( (data[3].fvalue < (float)0.94688600302)) {
        sum += (float)0.025337992236;
      } else {
        sum += (float)-0.0033052493818;
      }
    }
  }
  if ( (data[0].fvalue < (float)300.71749878)) {
    if ( (data[0].fvalue < (float)98.114105225)) {
      if ( (data[1].fvalue < (float)64.983100891)) {
        sum += (float)-0.03387889266;
      } else {
        sum += (float)-0.055289454758;
      }
    } else {
      if ( (data[2].fvalue < (float)2.481085062)) {
        sum += (float)-0.0062602008693;
      } else {
        sum += (float)-0.039354905486;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)2.5371499062)) {
      if ( (data[2].fvalue < (float)2.3823199272)) {
        sum += (float)0.027629185468;
      } else {
        sum += (float)-0.0067986026406;
      }
    } else {
      if ( (data[3].fvalue < (float)1.9753149748)) {
        sum += (float)-0.0058621931821;
      } else {
        sum += (float)0.012883302756;
      }
    }
  }
  if ( (data[1].fvalue < (float)8.0313549042)) {
    if ( (data[2].fvalue < (float)2.365639925)) {
      if ( (data[3].fvalue < (float)2.0716149807)) {
        sum += (float)0.0024253574666;
      } else {
        sum += (float)0.030149891973;
      }
    } else {
      if ( (data[2].fvalue < (float)2.6767699718)) {
        sum += (float)-0.0093473922461;
      } else {
        sum += (float)-0.032354533672;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)17.587551117)) {
      if ( (data[3].fvalue < (float)2.0106549263)) {
        sum += (float)-0.014323956333;
      } else {
        sum += (float)0.0031767149922;
      }
    } else {
      if ( (data[1].fvalue < (float)33.931049347)) {
        sum += (float)-0.02665027976;
      } else {
        sum += (float)-0.044232327491;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.40863999724)) {
    if ( (data[2].fvalue < (float)0.2030300051)) {
      if ( (data[1].fvalue < (float)0.55159246922)) {
        sum += (float)0.023862758651;
      } else {
        sum += (float)-0.075486935675;
      }
    } else {
      if ( (data[0].fvalue < (float)240.72949219)) {
        sum += (float)-0.053074132651;
      } else {
        sum += (float)-0.02104592137;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.94529247284)) {
      if ( (data[0].fvalue < (float)91.940353394)) {
        sum += (float)-0.044343456626;
      } else {
        sum += (float)0.026278642938;
      }
    } else {
      if ( (data[0].fvalue < (float)258.8994751)) {
        sum += (float)-0.017323156819;
      } else {
        sum += (float)-6.7341607064e-06;
      }
    }
  }
  if ( (data[1].fvalue < (float)1.5155400038)) {
    if ( (data[3].fvalue < (float)1.427670002)) {
      if ( (data[2].fvalue < (float)0.55939352512)) {
        sum += (float)-0.012210360728;
      } else {
        sum += (float)0.052734602243;
      }
    } else {
      if ( (data[0].fvalue < (float)399.70751953)) {
        sum += (float)-0.0028411445674;
      } else {
        sum += (float)0.022623190656;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)2.4701750278)) {
      if ( (data[3].fvalue < (float)1.9752999544)) {
        sum += (float)-0.0066006728448;
      } else {
        sum += (float)0.017142841592;
      }
    } else {
      if ( (data[0].fvalue < (float)275.48101807)) {
        sum += (float)-0.037785809487;
      } else {
        sum += (float)-0.019061710685;
      }
    }
  }
  if ( (data[1].fvalue < (float)4.9935250282)) {
    if ( (data[3].fvalue < (float)1.3725750446)) {
      if ( (data[2].fvalue < (float)0.56603401899)) {
        sum += (float)-0.022974414751;
      } else {
        sum += (float)0.030384931713;
      }
    } else {
      if ( (data[2].fvalue < (float)2.6714599133)) {
        sum += (float)0.0023718157317;
      } else {
        sum += (float)-0.027930503711;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)17.587551117)) {
      if ( (data[3].fvalue < (float)1.9737449884)) {
        sum += (float)-0.0095679489896;
      } else {
        sum += (float)0.0055434885435;
      }
    } else {
      if ( (data[1].fvalue < (float)64.983100891)) {
        sum += (float)-0.025074288249;
      } else {
        sum += (float)-0.048661310226;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.38275501132)) {
    if ( (data[2].fvalue < (float)0.2030300051)) {
      if ( (data[1].fvalue < (float)0.71164298058)) {
        sum += (float)0.0014537929092;
      } else {
        sum += (float)-0.068265303969;
      }
    } else {
      if ( (data[0].fvalue < (float)313.44549561)) {
        sum += (float)-0.042920384556;
      } else {
        sum += (float)-0.015359542333;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.90790247917)) {
      if ( (data[2].fvalue < (float)0.63148903847)) {
        sum += (float)-0.00089173356537;
      } else {
        sum += (float)0.030556960031;
      }
    } else {
      if ( (data[1].fvalue < (float)1.2863149643)) {
        sum += (float)0.023877000436;
      } else {
        sum += (float)-0.0060190954246;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.6465849876)) {
    if ( (data[3].fvalue < (float)2.0500049591)) {
      if ( (data[3].fvalue < (float)1.2083449364)) {
        sum += (float)0.0076815648936;
      } else {
        sum += (float)-0.011809502728;
      }
    } else {
      if ( (data[0].fvalue < (float)145.1000061)) {
        sum += (float)-0.030009418726;
      } else {
        sum += (float)0.01749917306;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)355.68850708)) {
      if ( (data[1].fvalue < (float)2.4121351242)) {
        sum += (float)-0.0076378472149;
      } else {
        sum += (float)-0.040902674198;
      }
    } else {
      if ( (data[1].fvalue < (float)10.500900269)) {
        sum += (float)-0.019913939759;
      } else {
        sum += (float)0.15380772948;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.43299749494)) {
    if ( (data[2].fvalue < (float)0.2030300051)) {
      if ( (data[1].fvalue < (float)0.55159246922)) {
        sum += (float)0.02403967455;
      } else {
        sum += (float)-0.063252463937;
      }
    } else {
      if ( (data[3].fvalue < (float)0.53604996204)) {
        sum += (float)-0.00788232591;
      } else {
        sum += (float)-0.033771950752;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.90790247917)) {
      if ( (data[0].fvalue < (float)85.974647522)) {
        sum += (float)-0.045418292284;
      } else {
        sum += (float)0.023047741503;
      }
    } else {
      if ( (data[1].fvalue < (float)1.5155249834)) {
        sum += (float)0.0184913259;
      } else {
        sum += (float)-0.0052972673438;
      }
    }
  }
  if ( (data[1].fvalue < (float)6.4500098228)) {
    if ( (data[2].fvalue < (float)2.2975399494)) {
      if ( (data[2].fvalue < (float)0.46568602324)) {
        sum += (float)-0.024547444656;
      } else {
        sum += (float)0.010324834846;
      }
    } else {
      if ( (data[2].fvalue < (float)2.6767699718)) {
        sum += (float)-0.006766137667;
      } else {
        sum += (float)-0.024238098413;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)21.432498932)) {
      if ( (data[3].fvalue < (float)1.9520050287)) {
        sum += (float)-0.010237012058;
      } else {
        sum += (float)0.003671776969;
      }
    } else {
      if ( (data[1].fvalue < (float)64.983100891)) {
        sum += (float)-0.025743132457;
      } else {
        sum += (float)-0.044405147433;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.4707150459)) {
    if ( (data[3].fvalue < (float)1.9752999544)) {
      if ( (data[3].fvalue < (float)1.2203099728)) {
        sum += (float)0.0067138383165;
      } else {
        sum += (float)-0.011957133189;
      }
    } else {
      if ( (data[0].fvalue < (float)164.80551147)) {
        sum += (float)-0.019598741084;
      } else {
        sum += (float)0.020491754636;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)363.42749023)) {
      if ( (data[2].fvalue < (float)2.7033100128)) {
        sum += (float)-0.020941229537;
      } else {
        sum += (float)-0.035034969449;
      }
    } else {
      if ( (data[3].fvalue < (float)2.4421999454)) {
        sum += (float)0.00027156219585;
      } else {
        sum += (float)-0.017014393583;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.2624605)) {
    if ( (data[0].fvalue < (float)246.37200928)) {
      if ( (data[0].fvalue < (float)208.02850342)) {
        sum += (float)-0.063396029174;
      } else {
        sum += (float)-0.094543643296;
      }
    } else {
      if ( (data[2].fvalue < (float)0.17924299836)) {
        sum += (float)-0.057124983519;
      } else {
        sum += (float)-0.020953865722;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.7303340435)) {
      if ( (data[2].fvalue < (float)0.63097703457)) {
        sum += (float)-0.0012964518974;
      } else {
        sum += (float)0.031394839287;
      }
    } else {
      if ( (data[1].fvalue < (float)4.5310201645)) {
        sum += (float)0.0056417002343;
      } else {
        sum += (float)-0.0071291550994;
      }
    }
  }
  if ( (data[0].fvalue < (float)121.36750031)) {
    if ( (data[3].fvalue < (float)1.8039799929)) {
      if ( (data[3].fvalue < (float)1.3867050409)) {
        sum += (float)-0.025044022128;
      } else {
        sum += (float)0.00473583024;
      }
    } else {
      if ( (data[0].fvalue < (float)42.21585083)) {
        sum += (float)-0.0068734060042;
      } else {
        sum += (float)-0.037839114666;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)2.3993051052)) {
      if ( (data[3].fvalue < (float)2.0922100544)) {
        sum += (float)-0.001072455314;
      } else {
        sum += (float)0.023003621027;
      }
    } else {
      if ( (data[2].fvalue < (float)2.6572899818)) {
        sum += (float)-0.0074167461134;
      } else {
        sum += (float)-0.021317591891;
      }
    }
  }
  if ( (data[1].fvalue < (float)1.2863149643)) {
    if ( (data[0].fvalue < (float)474.21697998)) {
      if ( (data[2].fvalue < (float)2.2145550251)) {
        sum += (float)0.017231006175;
      } else {
        sum += (float)-0.017100231722;
      }
    } else {
      if ( (data[3].fvalue < (float)1.4269349575)) {
        sum += (float)0.050022281706;
      } else {
        sum += (float)0.025858258829;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.40933251381)) {
      if ( (data[2].fvalue < (float)0.20673599839)) {
        sum += (float)-0.052968710661;
      } else {
        sum += (float)-0.020384809002;
      }
    } else {
      if ( (data[3].fvalue < (float)1.0034149885)) {
        sum += (float)0.013381307013;
      } else {
        sum += (float)-0.0044921110384;
      }
    }
  }
  if ( (data[1].fvalue < (float)10.127250671)) {
    if ( (data[3].fvalue < (float)1.2083449364)) {
      if ( (data[2].fvalue < (float)0.63712751865)) {
        sum += (float)-0.012992857955;
      } else {
        sum += (float)0.01944786869;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8666449785)) {
        sum += (float)-0.0096677988768;
      } else {
        sum += (float)0.0057390979491;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)21.432498932)) {
      if ( (data[2].fvalue < (float)0.25822550058)) {
        sum += (float)-0.063374869525;
      } else {
        sum += (float)-0.00750730047;
      }
    } else {
      if ( (data[1].fvalue < (float)64.983100891)) {
        sum += (float)-0.021475099027;
      } else {
        sum += (float)-0.039947174489;
      }
    }
  }
  if ( (data[0].fvalue < (float)300.71749878)) {
    if ( (data[3].fvalue < (float)0.68101751804)) {
      if ( (data[2].fvalue < (float)0.34830498695)) {
        sum += (float)-0.044497203082;
      } else {
        sum += (float)0.020108267665;
      }
    } else {
      if ( (data[2].fvalue < (float)0.58807301521)) {
        sum += (float)-0.040941480547;
      } else {
        sum += (float)-0.0079339444637;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)3.8517150879)) {
      if ( (data[3].fvalue < (float)1.372699976)) {
        sum += (float)0.023886539042;
      } else {
        sum += (float)0.00487770373;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8718700409)) {
        sum += (float)-0.0075868912973;
      } else {
        sum += (float)0.0096149696037;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.3993051052)) {
    if ( (data[3].fvalue < (float)1.9689600468)) {
      if ( (data[3].fvalue < (float)1.3731850386)) {
        sum += (float)0.0038518707734;
      } else {
        sum += (float)-0.010984095745;
      }
    } else {
      if ( (data[0].fvalue < (float)125.97100067)) {
        sum += (float)-0.026823807508;
      } else {
        sum += (float)0.01797102578;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)274.875)) {
      if ( (data[2].fvalue < (float)2.8599050045)) {
        sum += (float)-0.020766207948;
      } else {
        sum += (float)-0.040212515742;
      }
    } else {
      if ( (data[2].fvalue < (float)2.6476900578)) {
        sum += (float)-0.0031092024874;
      } else {
        sum += (float)-0.016252858564;
      }
    }
  }
  if ( (data[1].fvalue < (float)1.2863149643)) {
    if ( (data[0].fvalue < (float)474.21697998)) {
      if ( (data[2].fvalue < (float)2.0677847862)) {
        sum += (float)0.016170324758;
      } else {
        sum += (float)-0.01237573754;
      }
    } else {
      if ( (data[2].fvalue < (float)0.46779501438)) {
        sum += (float)-0.014022620395;
      } else {
        sum += (float)0.033916022629;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.26129350066)) {
      if ( (data[0].fvalue < (float)246.37200928)) {
        sum += (float)-0.061699774116;
      } else {
        sum += (float)-0.030183700845;
      }
    } else {
      if ( (data[3].fvalue < (float)0.66418755054)) {
        sum += (float)0.0154297892;
      } else {
        sum += (float)-0.0027948110364;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.45051801205)) {
    if ( (data[2].fvalue < (float)0.17920149863)) {
      if ( (data[1].fvalue < (float)0.52085000277)) {
        sum += (float)0.071883507073;
      } else {
        sum += (float)-0.050184059888;
      }
    } else {
      if ( (data[0].fvalue < (float)313.64147949)) {
        sum += (float)-0.029179727659;
      } else {
        sum += (float)-0.0076212747954;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)1.0655750036)) {
      if ( (data[1].fvalue < (float)4.6151447296)) {
        sum += (float)0.027035145089;
      } else {
        sum += (float)0.0042557390407;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8661650419)) {
        sum += (float)-0.0078358948231;
      } else {
        sum += (float)0.0033541198354;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.3590650558)) {
    if ( (data[3].fvalue < (float)2.1370849609)) {
      if ( (data[1].fvalue < (float)5.1264500618)) {
        sum += (float)0.005425542593;
      } else {
        sum += (float)-0.006004861556;
      }
    } else {
      if ( (data[0].fvalue < (float)126.00350189)) {
        sum += (float)-0.025248942897;
      } else {
        sum += (float)0.021585462615;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)274.875)) {
      if ( (data[2].fvalue < (float)2.8599050045)) {
        sum += (float)-0.018698554486;
      } else {
        sum += (float)-0.037208970636;
      }
    } else {
      if ( (data[2].fvalue < (float)2.6476900578)) {
        sum += (float)-0.0026520048268;
      } else {
        sum += (float)-0.014911198989;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.2110750675)) {
    if ( (data[3].fvalue < (float)2.1639449596)) {
      if ( (data[1].fvalue < (float)5.1264500618)) {
        sum += (float)0.005642764736;
      } else {
        sum += (float)-0.0050830072723;
      }
    } else {
      if ( (data[0].fvalue < (float)126.00350189)) {
        sum += (float)-0.020920960233;
      } else {
        sum += (float)0.026420516893;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)224.59249878)) {
      if ( (data[2].fvalue < (float)2.7037100792)) {
        sum += (float)-0.016065547243;
      } else {
        sum += (float)-0.034758120775;
      }
    } else {
      if ( (data[2].fvalue < (float)2.6476900578)) {
        sum += (float)-0.0028540471103;
      } else {
        sum += (float)-0.013613335788;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.631480515)) {
    if ( (data[3].fvalue < (float)0.44273149967)) {
      if ( (data[2].fvalue < (float)0.25679349899)) {
        sum += (float)-0.029019242153;
      } else {
        sum += (float)0.0076874527149;
      }
    } else {
      if ( (data[0].fvalue < (float)262.32449341)) {
        sum += (float)-0.031740803272;
      } else {
        sum += (float)-0.014168323949;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)1.07427001)) {
      if ( (data[0].fvalue < (float)85.976501465)) {
        sum += (float)-0.043391186744;
      } else {
        sum += (float)0.016950534657;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8661650419)) {
        sum += (float)-0.0068028005771;
      } else {
        sum += (float)0.0028502333444;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.1889550686)) {
    if ( (data[3].fvalue < (float)1.9690899849)) {
      if ( (data[3].fvalue < (float)1.3731850386)) {
        sum += (float)0.0033824064303;
      } else {
        sum += (float)-0.0077590043657;
      }
    } else {
      if ( (data[0].fvalue < (float)152.33000183)) {
        sum += (float)-0.01358956378;
      } else {
        sum += (float)0.019118295982;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)224.59249878)) {
      if ( (data[3].fvalue < (float)1.6533499956)) {
        sum += (float)0.02438749373;
      } else {
        sum += (float)-0.020233806223;
      }
    } else {
      if ( (data[2].fvalue < (float)2.6160049438)) {
        sum += (float)-0.0020056625362;
      } else {
        sum += (float)-0.011950258166;
      }
    }
  }
  if ( (data[1].fvalue < (float)1.5155400038)) {
    if ( (data[0].fvalue < (float)405.84448242)) {
      if ( (data[2].fvalue < (float)2.230809927)) {
        sum += (float)0.0050088865682;
      } else {
        sum += (float)-0.018923467025;
      }
    } else {
      if ( (data[3].fvalue < (float)1.4288250208)) {
        sum += (float)0.036399479955;
      } else {
        sum += (float)0.013142253272;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.63148498535)) {
      if ( (data[3].fvalue < (float)0.44233000278)) {
        sum += (float)0.00230738963;
      } else {
        sum += (float)-0.019716611132;
      }
    } else {
      if ( (data[3].fvalue < (float)0.67391598225)) {
        sum += (float)0.022388225421;
      } else {
        sum += (float)-0.0016348870704;
      }
    }
  }
  if ( (data[1].fvalue < (float)16.374799728)) {
    if ( (data[2].fvalue < (float)2.2989349365)) {
      if ( (data[3].fvalue < (float)2.2486948967)) {
        sum += (float)0.00069345254451;
      } else {
        sum += (float)0.020871913061;
      }
    } else {
      if ( (data[0].fvalue < (float)258.77850342)) {
        sum += (float)-0.017015181482;
      } else {
        sum += (float)-0.0051916330121;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)1.5568649769)) {
      if ( (data[3].fvalue < (float)0.50605297089)) {
        sum += (float)0.0042153988034;
      } else {
        sum += (float)-0.025342723355;
      }
    } else {
      if ( (data[2].fvalue < (float)1.5826849937)) {
        sum += (float)0.051992673427;
      } else {
        sum += (float)-0.0096076279879;
      }
    }
  }
  if ( (data[1].fvalue < (float)0.9004535079)) {
    if ( (data[2].fvalue < (float)2.2794299126)) {
      if ( (data[2].fvalue < (float)0.55960649252)) {
        sum += (float)-0.0054344474338;
      } else {
        sum += (float)0.032250341028;
      }
    } else {
      if ( (data[0].fvalue < (float)380.32598877)) {
        sum += (float)-0.04770931229;
      } else {
        sum += (float)0.0096486015245;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.31738251448)) {
      if ( (data[2].fvalue < (float)0.17920149863)) {
        sum += (float)-0.043964762241;
      } else {
        sum += (float)-0.017360193655;
      }
    } else {
      if ( (data[3].fvalue < (float)0.82520347834)) {
        sum += (float)0.010157017969;
      } else {
        sum += (float)-0.0020168197807;
      }
    }
  }
  if ( (data[0].fvalue < (float)81.292098999)) {
    if ( (data[1].fvalue < (float)6.4030799866)) {
      if ( (data[0].fvalue < (float)67.413253784)) {
        sum += (float)-0.073349878192;
      } else {
        sum += (float)-0.034904137254;
      }
    } else {
      if ( (data[3].fvalue < (float)1.12616992)) {
        sum += (float)-0.037472072989;
      } else {
        sum += (float)-0.0080394214019;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.62037301064)) {
      if ( (data[3].fvalue < (float)0.53839451075)) {
        sum += (float)-0.00087584770517;
      } else {
        sum += (float)-0.017509102821;
      }
    } else {
      if ( (data[3].fvalue < (float)1.1029549837)) {
        sum += (float)0.012966494076;
      } else {
        sum += (float)-0.0013229199685;
      }
    }
  }
  if ( (data[1].fvalue < (float)2.0608301163)) {
    if ( (data[0].fvalue < (float)353.04049683)) {
      if ( (data[3].fvalue < (float)1.4008100033)) {
        sum += (float)0.0071387649514;
      } else {
        sum += (float)-0.013841934502;
      }
    } else {
      if ( (data[3].fvalue < (float)1.5042049885)) {
        sum += (float)0.025298565626;
      } else {
        sum += (float)0.0084804203361;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)522.27502441)) {
      if ( (data[1].fvalue < (float)7.5589900017)) {
        sum += (float)0.0039023682475;
      } else {
        sum += (float)-0.0050872093998;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8698649406)) {
        sum += (float)-0.01639434509;
      } else {
        sum += (float)0.0017398454947;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.75933003426)) {
    if ( (data[3].fvalue < (float)0.45740002394)) {
      if ( (data[2].fvalue < (float)0.25799101591)) {
        sum += (float)-0.027849799022;
      } else {
        sum += (float)0.0078550269827;
      }
    } else {
      if ( (data[0].fvalue < (float)174.43649292)) {
        sum += (float)-0.027563540265;
      } else {
        sum += (float)-0.010625600815;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)1.1029549837)) {
      if ( (data[1].fvalue < (float)3.7301249504)) {
        sum += (float)0.032279141247;
      } else {
        sum += (float)0.0076187509112;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8661650419)) {
        sum += (float)-0.0055191046558;
      } else {
        sum += (float)0.0028158167843;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.1889550686)) {
    if ( (data[3].fvalue < (float)2.1471350193)) {
      if ( (data[1].fvalue < (float)9.9971256256)) {
        sum += (float)0.0019058991456;
      } else {
        sum += (float)-0.0093628615141;
      }
    } else {
      if ( (data[0].fvalue < (float)125.64399719)) {
        sum += (float)-0.016652485356;
      } else {
        sum += (float)0.02022800222;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)224.59249878)) {
      if ( (data[3].fvalue < (float)1.6533499956)) {
        sum += (float)0.024026388302;
      } else {
        sum += (float)-0.01684785448;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8145450354)) {
        sum += (float)-0.019328035414;
      } else {
        sum += (float)-0.0030540160369;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.45051801205)) {
    if ( (data[2].fvalue < (float)0.17920149863)) {
      if ( (data[3].fvalue < (float)0.91316598654)) {
        sum += (float)-0.038706269115;
      } else {
        sum += (float)0.1115302369;
      }
    } else {
      if ( (data[0].fvalue < (float)313.64147949)) {
        sum += (float)-0.021454257891;
      } else {
        sum += (float)-0.0041141058318;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.74586600065)) {
      if ( (data[0].fvalue < (float)83.485153198)) {
        sum += (float)-0.04099323228;
      } else {
        sum += (float)0.014309453778;
      }
    } else {
      if ( (data[0].fvalue < (float)300.71749878)) {
        sum += (float)-0.0052102911286;
      } else {
        sum += (float)0.0018012671499;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.5643799305)) {
    if ( (data[3].fvalue < (float)2.0715949535)) {
      if ( (data[1].fvalue < (float)2.0608301163)) {
        sum += (float)0.010169134475;
      } else {
        sum += (float)-0.0025664232671;
      }
    } else {
      if ( (data[2].fvalue < (float)2.1138000488)) {
        sum += (float)0.017447767779;
      } else {
        sum += (float)0.00097045797156;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)2.3954899311)) {
      if ( (data[2].fvalue < (float)2.5655100346)) {
        sum += (float)-0.12390302867;
      } else {
        sum += (float)6.854669482e-05;
      }
    } else {
      if ( (data[0].fvalue < (float)347.98748779)) {
        sum += (float)-0.019991783425;
      } else {
        sum += (float)-0.0083015728742;
      }
    }
  }
  if ( (data[1].fvalue < (float)0.9004535079)) {
    if ( (data[0].fvalue < (float)301.19299316)) {
      if ( (data[2].fvalue < (float)0.45464551449)) {
        sum += (float)-0.15145047009;
      } else {
        sum += (float)-0.024209737778;
      }
    } else {
      if ( (data[3].fvalue < (float)2.6318149567)) {
        sum += (float)0.023265331984;
      } else {
        sum += (float)-0.014489144087;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.75933003426)) {
      if ( (data[3].fvalue < (float)0.45740002394)) {
        sum += (float)0.00309596234;
      } else {
        sum += (float)-0.012077495456;
      }
    } else {
      if ( (data[3].fvalue < (float)1.1803500652)) {
        sum += (float)0.01017527841;
      } else {
        sum += (float)-0.0019712788053;
      }
    }
  }
  if ( (data[0].fvalue < (float)81.292098999)) {
    if ( (data[1].fvalue < (float)6.4030799866)) {
      if ( (data[0].fvalue < (float)65.059295654)) {
        sum += (float)-0.071128539741;
      } else {
        sum += (float)-0.033484410495;
      }
    } else {
      if ( (data[2].fvalue < (float)1.4786900282)) {
        sum += (float)-0.026426916942;
      } else {
        sum += (float)-0.0012689584401;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)2.6235949993)) {
      if ( (data[3].fvalue < (float)2.071449995)) {
        sum += (float)-0.00054625072517;
      } else {
        sum += (float)0.0073116752319;
      }
    } else {
      if ( (data[1].fvalue < (float)2.4453048706)) {
        sum += (float)-0.00052085495554;
      } else {
        sum += (float)-0.014278270304;
      }
    }
  }
  if ( (data[1].fvalue < (float)17.587551117)) {
    if ( (data[2].fvalue < (float)2.1724250317)) {
      if ( (data[3].fvalue < (float)1.8798199892)) {
        sum += (float)-0.00022609798179;
      } else {
        sum += (float)0.011400158517;
      }
    } else {
      if ( (data[0].fvalue < (float)223.89801025)) {
        sum += (float)-0.013625613414;
      } else {
        sum += (float)-0.0034174274188;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)1.6683850288)) {
      if ( (data[3].fvalue < (float)0.50605297089)) {
        sum += (float)0.0031795713585;
      } else {
        sum += (float)-0.020466944203;
      }
    } else {
      if ( (data[2].fvalue < (float)1.7032999992)) {
        sum += (float)0.04620391503;
      } else {
        sum += (float)-0.0065565132536;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.2624605)) {
    if ( (data[0].fvalue < (float)246.37200928)) {
      if ( (data[0].fvalue < (float)221.61250305)) {
        sum += (float)-0.036601018161;
      } else {
        sum += (float)-0.07920229435;
      }
    } else {
      if ( (data[2].fvalue < (float)0.16454949975)) {
        sum += (float)-0.034553039819;
      } else {
        sum += (float)-0.0067500076257;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.65996897221)) {
      if ( (data[2].fvalue < (float)0.76188445091)) {
        sum += (float)0.0026115390938;
      } else {
        sum += (float)0.021718256176;
      }
    } else {
      if ( (data[2].fvalue < (float)0.98813349009)) {
        sum += (float)-0.0086904680356;
      } else {
        sum += (float)0.00054989033379;
      }
    }
  }
  if ( (data[1].fvalue < (float)0.9004535079)) {
    if ( (data[2].fvalue < (float)2.2794299126)) {
      if ( (data[2].fvalue < (float)0.55960649252)) {
        sum += (float)-0.0071510463022;
      } else {
        sum += (float)0.024912059307;
      }
    } else {
      if ( (data[0].fvalue < (float)380.32598877)) {
        sum += (float)-0.042525798082;
      } else {
        sum += (float)0.0068350206129;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)74.70765686)) {
      if ( (data[1].fvalue < (float)6.4030799866)) {
        sum += (float)-0.056326765567;
      } else {
        sum += (float)-0.011860857718;
      }
    } else {
      if ( (data[3].fvalue < (float)1.2858700752)) {
        sum += (float)0.0034349274356;
      } else {
        sum += (float)-0.0020542282145;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.45051801205)) {
    if ( (data[2].fvalue < (float)0.2030300051)) {
      if ( (data[1].fvalue < (float)3.8362898827)) {
        sum += (float)-0.040988922119;
      } else {
        sum += (float)-0.018711291254;
      }
    } else {
      if ( (data[0].fvalue < (float)133.83248901)) {
        sum += (float)-0.038787331432;
      } else {
        sum += (float)-0.0058344323188;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.86012649536)) {
      if ( (data[0].fvalue < (float)83.486343384)) {
        sum += (float)-0.035001520067;
      } else {
        sum += (float)0.010169854388;
      }
    } else {
      if ( (data[2].fvalue < (float)1.300999999)) {
        sum += (float)-0.0061071179807;
      } else {
        sum += (float)0.00078974367352;
      }
    }
  }
  if ( (data[1].fvalue < (float)6.2384548187)) {
    if ( (data[3].fvalue < (float)1.4370999336)) {
      if ( (data[2].fvalue < (float)0.7398494482)) {
        sum += (float)-0.0047825532965;
      } else {
        sum += (float)0.013459580019;
      }
    } else {
      if ( (data[3].fvalue < (float)1.7292649746)) {
        sum += (float)-0.011806691065;
      } else {
        sum += (float)0.0018656889442;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)499.03851318)) {
      if ( (data[3].fvalue < (float)1.9511649609)) {
        sum += (float)-0.004021983128;
      } else {
        sum += (float)0.0034124783706;
      }
    } else {
      if ( (data[3].fvalue < (float)1.7398850918)) {
        sum += (float)-0.025744089857;
      } else {
        sum += (float)-0.0021859733388;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.1691699028)) {
    if ( (data[3].fvalue < (float)2.2494750023)) {
      if ( (data[1].fvalue < (float)6.3344898224)) {
        sum += (float)0.0032739432063;
      } else {
        sum += (float)-0.0036770731676;
      }
    } else {
      if ( (data[0].fvalue < (float)150.56950378)) {
        sum += (float)-0.0089934105054;
      } else {
        sum += (float)0.019969586283;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)174.21398926)) {
      if ( (data[0].fvalue < (float)31.783748627)) {
        sum += (float)0.016637487337;
      } else {
        sum += (float)-0.016513103619;
      }
    } else {
      if ( (data[2].fvalue < (float)2.7397949696)) {
        sum += (float)-0.0017888707807;
      } else {
        sum += (float)-0.011892414652;
      }
    }
  }
  if ( (data[1].fvalue < (float)1.2868349552)) {
    if ( (data[0].fvalue < (float)474.21697998)) {
      if ( (data[3].fvalue < (float)2.313849926)) {
        sum += (float)0.0055174021982;
      } else {
        sum += (float)-0.017338020727;
      }
    } else {
      if ( (data[2].fvalue < (float)0.19679300487)) {
        sum += (float)-0.057658292353;
      } else {
        sum += (float)0.021110838279;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)522.06750488)) {
      if ( (data[1].fvalue < (float)7.6281900406)) {
        sum += (float)0.0030608677771;
      } else {
        sum += (float)-0.0030948594213;
      }
    } else {
      if ( (data[1].fvalue < (float)2.6438000202)) {
        sum += (float)0.0096007566899;
      } else {
        sum += (float)-0.011534239165;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.115170002)) {
    if ( (data[3].fvalue < (float)2.2104399204)) {
      if ( (data[1].fvalue < (float)12.659049988)) {
        sum += (float)0.0012366867159;
      } else {
        sum += (float)-0.008818349801;
      }
    } else {
      if ( (data[0].fvalue < (float)125.64399719)) {
        sum += (float)-0.013753729872;
      } else {
        sum += (float)0.019352871925;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)178.74299622)) {
      if ( (data[3].fvalue < (float)1.5816049576)) {
        sum += (float)0.059723135084;
      } else {
        sum += (float)-0.014625461772;
      }
    } else {
      if ( (data[2].fvalue < (float)2.7397949696)) {
        sum += (float)-0.0014132722281;
      } else {
        sum += (float)-0.010839125142;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.2624605)) {
    if ( (data[0].fvalue < (float)246.37200928)) {
      if ( (data[0].fvalue < (float)208.02850342)) {
        sum += (float)-0.029387492687;
      } else {
        sum += (float)-0.0656555444;
      }
    } else {
      if ( (data[0].fvalue < (float)257.89001465)) {
        sum += (float)0.064271770418;
      } else {
        sum += (float)-0.014855245128;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.65996897221)) {
      if ( (data[2].fvalue < (float)0.90735602379)) {
        sum += (float)0.0040270048194;
      } else {
        sum += (float)0.023193091154;
      }
    } else {
      if ( (data[2].fvalue < (float)0.98813349009)) {
        sum += (float)-0.0077457018197;
      } else {
        sum += (float)0.00054961937713;
      }
    }
  }
  if ( (data[3].fvalue < (float)1.2858700752)) {
    if ( (data[2].fvalue < (float)0.90667450428)) {
      if ( (data[3].fvalue < (float)0.45277300477)) {
        sum += (float)0.005490930751;
      } else {
        sum += (float)-0.0062780813314;
      }
    } else {
      if ( (data[1].fvalue < (float)3.9485349655)) {
        sum += (float)0.021266547963;
      } else {
        sum += (float)0.0046355081722;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)1.7602499723)) {
      if ( (data[0].fvalue < (float)129.07800293)) {
        sum += (float)0.01521269884;
      } else {
        sum += (float)-0.0087305875495;
      }
    } else {
      if ( (data[2].fvalue < (float)2.1138000488)) {
        sum += (float)0.0076307789423;
      } else {
        sum += (float)-0.0035116069485;
      }
    }
  }
  if ( (data[1].fvalue < (float)0.9004535079)) {
    if ( (data[0].fvalue < (float)301.19299316)) {
      if ( (data[2].fvalue < (float)2.1221199036)) {
        sum += (float)-0.01248932071;
      } else {
        sum += (float)-0.071037448943;
      }
    } else {
      if ( (data[3].fvalue < (float)2.6318149567)) {
        sum += (float)0.018107930198;
      } else {
        sum += (float)-0.013329933397;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)516.79003906)) {
      if ( (data[0].fvalue < (float)306.64050293)) {
        sum += (float)-0.0024887488689;
      } else {
        sum += (float)0.0034278184175;
      }
    } else {
      if ( (data[1].fvalue < (float)3.2517549992)) {
        sum += (float)0.0059548048303;
      } else {
        sum += (float)-0.0110363774;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.2030300051)) {
    if ( (data[1].fvalue < (float)3.8362898827)) {
      if ( (data[3].fvalue < (float)0.90397399664)) {
        sum += (float)-0.037770606577;
      } else {
        sum += (float)0.059529364109;
      }
    } else {
      if ( (data[0].fvalue < (float)479.15148926)) {
        sum += (float)-0.024155819789;
      } else {
        sum += (float)0.022711228579;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.82520347834)) {
      if ( (data[2].fvalue < (float)0.91275501251)) {
        sum += (float)0.00096117221983;
      } else {
        sum += (float)0.01589220576;
      }
    } else {
      if ( (data[2].fvalue < (float)1.300999999)) {
        sum += (float)-0.0053991223685;
      } else {
        sum += (float)0.00073911366053;
      }
    }
  }
  if ( (data[1].fvalue < (float)21.432498932)) {
    if ( (data[3].fvalue < (float)1.3731850386)) {
      if ( (data[2].fvalue < (float)0.76228499413)) {
        sum += (float)-0.0043439618312;
      } else {
        sum += (float)0.0070541403256;
      }
    } else {
      if ( (data[3].fvalue < (float)1.7685049772)) {
        sum += (float)-0.0077768764459;
      } else {
        sum += (float)0.0016172003234;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)2.125565052)) {
      if ( (data[0].fvalue < (float)154.59750366)) {
        sum += (float)-0.012816461734;
      } else {
        sum += (float)-0.043411877006;
      }
    } else {
      if ( (data[0].fvalue < (float)93.632446289)) {
        sum += (float)-0.008694103919;
      } else {
        sum += (float)0.021616538987;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.4707150459)) {
    if ( (data[3].fvalue < (float)2.2486948967)) {
      if ( (data[3].fvalue < (float)1.4115200043)) {
        sum += (float)0.0020733252168;
      } else {
        sum += (float)-0.0031882834155;
      }
    } else {
      if ( (data[0].fvalue < (float)182.48348999)) {
        sum += (float)-0.0058184256777;
      } else {
        sum += (float)0.011429786682;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)2.3569550514)) {
      if ( (data[3].fvalue < (float)2.355410099)) {
        sum += (float)-0.00075499777449;
      } else {
        sum += (float)0.12879090011;
      }
    } else {
      if ( (data[0].fvalue < (float)544.90301514)) {
        sum += (float)-0.011072746478;
      } else {
        sum += (float)0.0035814333241;
      }
    }
  }
  if ( (data[1].fvalue < (float)0.9004535079)) {
    if ( (data[0].fvalue < (float)327.1505127)) {
      if ( (data[2].fvalue < (float)2.1221199036)) {
        sum += (float)-0.0023906535935;
      } else {
        sum += (float)-0.056584812701;
      }
    } else {
      if ( (data[3].fvalue < (float)2.6318149567)) {
        sum += (float)0.017624316737;
      } else {
        sum += (float)-0.014204840176;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)495.2869873)) {
      if ( (data[0].fvalue < (float)319.79351807)) {
        sum += (float)-0.0020087126177;
      } else {
        sum += (float)0.0038928296417;
      }
    } else {
      if ( (data[1].fvalue < (float)2.8133149147)) {
        sum += (float)0.0069925710559;
      } else {
        sum += (float)-0.00825865753;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.1691699028)) {
    if ( (data[3].fvalue < (float)1.878584981)) {
      if ( (data[3].fvalue < (float)1.5168050528)) {
        sum += (float)0.001500169863;
      } else {
        sum += (float)-0.0071630040184;
      }
    } else {
      if ( (data[0].fvalue < (float)346.91650391)) {
        sum += (float)0.00050531449961;
      } else {
        sum += (float)0.014107394032;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)2.0500500202)) {
      if ( (data[1].fvalue < (float)0.69962149858)) {
        sum += (float)0.046947594732;
      } else {
        sum += (float)-0.010350360535;
      }
    } else {
      if ( (data[2].fvalue < (float)2.6572899818)) {
        sum += (float)0.00052515568677;
      } else {
        sum += (float)-0.0080724451691;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.5691845417)) {
    if ( (data[2].fvalue < (float)0.55473947525)) {
      if ( (data[0].fvalue < (float)132.75650024)) {
        sum += (float)-0.026017138734;
      } else {
        sum += (float)-0.0039747753181;
      }
    } else {
      if ( (data[2].fvalue < (float)0.56102699041)) {
        sum += (float)-0.06141775474;
      } else {
        sum += (float)-0.0093171996996;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.99368298054)) {
      if ( (data[1].fvalue < (float)3.3363399506)) {
        sum += (float)0.022280015051;
      } else {
        sum += (float)0.0033145409543;
      }
    } else {
      if ( (data[2].fvalue < (float)1.2872149944)) {
        sum += (float)-0.0053383051418;
      } else {
        sum += (float)0.00039412031765;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.2030300051)) {
    if ( (data[3].fvalue < (float)0.27182251215)) {
      if ( (data[3].fvalue < (float)0.25464701653)) {
        sum += (float)-0.0093367164955;
      } else {
        sum += (float)0.089452385902;
      }
    } else {
      if ( (data[0].fvalue < (float)121.96749878)) {
        sum += (float)0.026094228029;
      } else {
        sum += (float)-0.027495993301;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.59544551373)) {
      if ( (data[2].fvalue < (float)0.7589610219)) {
        sum += (float)0.0015729310689;
      } else {
        sum += (float)0.016773479059;
      }
    } else {
      if ( (data[2].fvalue < (float)0.98813349009)) {
        sum += (float)-0.0059918994084;
      } else {
        sum += (float)0.00058888259809;
      }
    }
  }
  if ( (data[0].fvalue < (float)74.70765686)) {
    if ( (data[1].fvalue < (float)8.7978343964)) {
      if ( (data[2].fvalue < (float)1.8413450718)) {
        sum += (float)-0.053499370813;
      } else {
        sum += (float)-0.018710328266;
      }
    } else {
      if ( (data[1].fvalue < (float)44.005199432)) {
        sum += (float)0.0061280881055;
      } else {
        sum += (float)-0.019149204716;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)2.1226050854)) {
      if ( (data[3].fvalue < (float)2.2947700024)) {
        sum += (float)0.00061454670504;
      } else {
        sum += (float)0.016081511974;
      }
    } else {
      if ( (data[0].fvalue < (float)152.27000427)) {
        sum += (float)-0.01416462101;
      } else {
        sum += (float)-0.0024773085024;
      }
    }
  }
  if ( (data[1].fvalue < (float)1.2868349552)) {
    if ( (data[0].fvalue < (float)474.21697998)) {
      if ( (data[3].fvalue < (float)2.2172551155)) {
        sum += (float)0.0041841357015;
      } else {
        sum += (float)-0.014496782795;
      }
    } else {
      if ( (data[3].fvalue < (float)1.4269349575)) {
        sum += (float)0.027292951941;
      } else {
        sum += (float)0.0099304774776;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)522.06750488)) {
      if ( (data[2].fvalue < (float)2.7484650612)) {
        sum += (float)0.0010071673896;
      } else {
        sum += (float)-0.01243358478;
      }
    } else {
      if ( (data[1].fvalue < (float)2.6438000202)) {
        sum += (float)0.0071180686355;
      } else {
        sum += (float)-0.0090584494174;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.45051801205)) {
    if ( (data[2].fvalue < (float)0.45027050376)) {
      if ( (data[2].fvalue < (float)0.17920149863)) {
        sum += (float)-0.022229794413;
      } else {
        sum += (float)-0.0054907621816;
      }
    } else {
      if ( (data[1].fvalue < (float)8.5283203125)) {
        sum += (float)-0.14307656884;
      } else {
        sum += (float)-0.032108318061;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)1.1803450584)) {
      if ( (data[0].fvalue < (float)105.70899963)) {
        sum += (float)-0.019042214379;
      } else {
        sum += (float)0.0051718093455;
      }
    } else {
      if ( (data[3].fvalue < (float)1.7602499723)) {
        sum += (float)-0.004126183223;
      } else {
        sum += (float)0.0012590779224;
      }
    }
  }
  if ( (data[1].fvalue < (float)6.80960989)) {
    if ( (data[3].fvalue < (float)1.4686950445)) {
      if ( (data[2].fvalue < (float)0.75803649426)) {
        sum += (float)-0.0035340269096;
      } else {
        sum += (float)0.0087573044002;
      }
    } else {
      if ( (data[3].fvalue < (float)1.7293150425)) {
        sum += (float)-0.009975777939;
      } else {
        sum += (float)0.0013005447108;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)1.5728000402)) {
      if ( (data[3].fvalue < (float)0.59546148777)) {
        sum += (float)0.0060860682279;
      } else {
        sum += (float)-0.00727536669;
      }
    } else {
      if ( (data[2].fvalue < (float)2.4707150459)) {
        sum += (float)0.0025839377195;
      } else {
        sum += (float)-0.0075016594492;
      }
    }
  }
  if ( (data[1].fvalue < (float)19.907249451)) {
    if ( (data[1].fvalue < (float)19.869949341)) {
      if ( (data[2].fvalue < (float)2.1247251034)) {
        sum += (float)0.0012863546144;
      } else {
        sum += (float)-0.0029552623164;
      }
    } else {
      if ( (data[1].fvalue < (float)19.885700226)) {
        sum += (float)0.22889259458;
      } else {
        sum += (float)0.037028219551;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)2.6301300526)) {
      if ( (data[0].fvalue < (float)26.786800385)) {
        sum += (float)0.012364375405;
      } else {
        sum += (float)-0.012217845768;
      }
    } else {
      if ( (data[0].fvalue < (float)178.28199768)) {
        sum += (float)0.015128304251;
      } else {
        sum += (float)0.15682815015;
      }
    }
  }
  if ( (data[1].fvalue < (float)0.9004535079)) {
    if ( (data[0].fvalue < (float)301.19299316)) {
      if ( (data[2].fvalue < (float)0.45464551449)) {
        sum += (float)-0.13097892702;
      } else {
        sum += (float)-0.019035967067;
      }
    } else {
      if ( (data[3].fvalue < (float)2.7619600296)) {
        sum += (float)0.013327419758;
      } else {
        sum += (float)-0.018131470308;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)495.2869873)) {
      if ( (data[0].fvalue < (float)346.26049805)) {
        sum += (float)-0.0012694246834;
      } else {
        sum += (float)0.0037314188667;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8494449854)) {
        sum += (float)-0.0087257670239;
      } else {
        sum += (float)0.0041580982506;
      }
    }
  }
  if ( (data[1].fvalue < (float)64.983100891)) {
    if ( (data[0].fvalue < (float)22.469749451)) {
      if ( (data[3].fvalue < (float)0.3560090065)) {
        sum += (float)0.33596619964;
      } else {
        sum += (float)0.080201722682;
      }
    } else {
      if ( (data[0].fvalue < (float)74.70765686)) {
        sum += (float)-0.012251428328;
      } else {
        sum += (float)0.0002210764651;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)2.9219698906)) {
      if ( (data[1].fvalue < (float)346.14752197)) {
        sum += (float)-0.025007238612;
      } else {
        sum += (float)0.12440129369;
      }
    } else {
      if ( (data[0].fvalue < (float)22.458400726)) {
        sum += (float)0.1970282346;
      } else {
        sum += (float)0.042184963822;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.631480515)) {
    if ( (data[0].fvalue < (float)132.75650024)) {
      if ( (data[1].fvalue < (float)3.5159301758)) {
        sum += (float)-0.088442981243;
      } else {
        sum += (float)-0.016577107832;
      }
    } else {
      if ( (data[2].fvalue < (float)0.62793898582)) {
        sum += (float)-0.0029633000959;
      } else {
        sum += (float)-0.0530285649;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)1.1803500652)) {
      if ( (data[1].fvalue < (float)4.7309799194)) {
        sum += (float)0.013599748723;
      } else {
        sum += (float)0.00063008809229;
      }
    } else {
      if ( (data[2].fvalue < (float)1.1528849602)) {
        sum += (float)-0.008102777414;
      } else {
        sum += (float)-6.9737063313e-05;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.115170002)) {
    if ( (data[3].fvalue < (float)2.2947700024)) {
      if ( (data[1].fvalue < (float)6.3344898224)) {
        sum += (float)0.0023151743226;
      } else {
        sum += (float)-0.0024038793053;
      }
    } else {
      if ( (data[0].fvalue < (float)125.64399719)) {
        sum += (float)-0.017665920779;
      } else {
        sum += (float)0.016124712303;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)1.4732300043)) {
      if ( (data[0].fvalue < (float)577.72802734)) {
        sum += (float)0.044093213975;
      } else {
        sum += (float)-0.050190776587;
      }
    } else {
      if ( (data[2].fvalue < (float)3.1086299419)) {
        sum += (float)-0.0028183569666;
      } else {
        sum += (float)-0.083078511059;
      }
    }
  }
  if ( (data[0].fvalue < (float)517.87548828)) {
    if ( (data[2].fvalue < (float)2.7495598793)) {
      if ( (data[0].fvalue < (float)319.79351807)) {
        sum += (float)-0.001095738844;
      } else {
        sum += (float)0.0032447555568;
      }
    } else {
      if ( (data[3].fvalue < (float)2.8337349892)) {
        sum += (float)-0.014591291547;
      } else {
        sum += (float)0.0070408866741;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)2.6438000202)) {
      if ( (data[2].fvalue < (float)0.48406648636)) {
        sum += (float)-0.023443907499;
      } else {
        sum += (float)0.01002406422;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8698649406)) {
        sum += (float)-0.012412361801;
      } else {
        sum += (float)0.0012500014855;
      }
    }
  }
  if ( (data[3].fvalue < (float)0.54064202309)) {
    if ( (data[0].fvalue < (float)83.76184845)) {
      if ( (data[0].fvalue < (float)36.685348511)) {
        sum += (float)0.0011916429503;
      } else {
        sum += (float)-0.049718063325;
      }
    } else {
      if ( (data[2].fvalue < (float)0.8796454668)) {
        sum += (float)0.0036410761531;
      } else {
        sum += (float)0.020010530949;
      }
    }
  } else {
    if ( (data[2].fvalue < (float)0.98813349009)) {
      if ( (data[1].fvalue < (float)6.3134350777)) {
        sum += (float)-0.0010499212658;
      } else {
        sum += (float)-0.010259264149;
      }
    } else {
      if ( (data[3].fvalue < (float)1.0736100674)) {
        sum += (float)0.008486523293;
      } else {
        sum += (float)-0.00036142428871;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.2030300051)) {
    if ( (data[2].fvalue < (float)0.20078149438)) {
      if ( (data[1].fvalue < (float)3.8362898827)) {
        sum += (float)-0.027313530445;
      } else {
        sum += (float)-0.0049506835639;
      }
    } else {
      if ( (data[1].fvalue < (float)1.4156249762)) {
        sum += (float)0.055442947894;
      } else {
        sum += (float)-0.097700692713;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.65996897221)) {
      if ( (data[0].fvalue < (float)516.74450684)) {
        sum += (float)0.007562851999;
      } else {
        sum += (float)-0.0091359680519;
      }
    } else {
      if ( (data[2].fvalue < (float)0.99228149652)) {
        sum += (float)-0.0049265492707;
      } else {
        sum += (float)0.00038008889533;
      }
    }
  }
  if ( (data[2].fvalue < (float)0.33475700021)) {
    if ( (data[0].fvalue < (float)249.11749268)) {
      if ( (data[3].fvalue < (float)0.40338951349)) {
        sum += (float)-0.0043643075041;
      } else {
        sum += (float)-0.032247480005;
      }
    } else {
      if ( (data[2].fvalue < (float)0.16076649725)) {
        sum += (float)-0.020124156028;
      } else {
        sum += (float)-0.00078728416702;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)0.90790247917)) {
      if ( (data[0].fvalue < (float)92.711250305)) {
        sum += (float)-0.021576348692;
      } else {
        sum += (float)0.0047037592158;
      }
    } else {
      if ( (data[2].fvalue < (float)1.3085150719)) {
        sum += (float)-0.0041464599781;
      } else {
        sum += (float)0.00056209828472;
      }
    }
  }
  if ( (data[2].fvalue < (float)2.115170002)) {
    if ( (data[3].fvalue < (float)1.8798199892)) {
      if ( (data[3].fvalue < (float)1.5168050528)) {
        sum += (float)0.0012173292926;
      } else {
        sum += (float)-0.0056131384335;
      }
    } else {
      if ( (data[0].fvalue < (float)346.89199829)) {
        sum += (float)0.00022948645346;
      } else {
        sum += (float)0.011697625741;
      }
    }
  } else {
    if ( (data[3].fvalue < (float)1.4123549461)) {
      if ( (data[1].fvalue < (float)10.871450424)) {
        sum += (float)0.084711924195;
      } else {
        sum += (float)-0.016029452905;
      }
    } else {
      if ( (data[2].fvalue < (float)2.1158750057)) {
        sum += (float)-0.07244143635;
      } else {
        sum += (float)-0.0024985300843;
      }
    }
  }
  if ( (data[0].fvalue < (float)585.74951172)) {
    if ( (data[0].fvalue < (float)585.49951172)) {
      if ( (data[2].fvalue < (float)0.26580250263)) {
        sum += (float)-0.011540686712;
      } else {
        sum += (float)0.0003621688229;
      }
    } else {
      if ( (data[2].fvalue < (float)2.5022249222)) {
        sum += (float)0.072246193886;
      } else {
        sum += (float)-0.040127586573;
      }
    }
  } else {
    if ( (data[1].fvalue < (float)2.7017550468)) {
      if ( (data[3].fvalue < (float)0.99128401279)) {
        sum += (float)0.030334150419;
      } else {
        sum += (float)0.0022109628189;
      }
    } else {
      if ( (data[3].fvalue < (float)1.8437299728)) {
        sum += (float)-0.021124755964;
      } else {
        sum += (float)-0.0043071946129;
      }
    }
  }
  if ( (data[1].fvalue < (float)0.9004535079)) {
    if ( (data[0].fvalue < (float)327.1505127)) {
      if ( (data[2].fvalue < (float)1.7002251148)) {
        sum += (float)0.0053499285132;
      } else {
        sum += (float)-0.038349833339;
      }
    } else {
      if ( (data[3].fvalue < (float)2.6318149567)) {
        sum += (float)0.012826310471;
      } else {
        sum += (float)-0.012012854218;
      }
    }
  } else {
    if ( (data[0].fvalue < (float)495.2869873)) {
      if ( (data[1].fvalue < (float)7.6180200577)) {
        sum += (float)0.0022599447984;
      } else {
        sum += (float)-0.0016926309327;
      }
    } else {
      if ( (data[1].fvalue < (float)4.0942049026)) {
        sum += (float)0.0025007396471;
      } else {
        sum += (float)-0.0082614021376;
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
