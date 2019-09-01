#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "L1TriggerConfig/L1GtConfigProducers/interface/L1GtStableParametersTrivialProducer.h"
#include "L1TriggerConfig/L1GtConfigProducers/interface/L1GtParametersTrivialProducer.h"

//
#include "L1TriggerConfig/L1GtConfigProducers/interface/L1GtPrescaleFactorsAlgoTrigTrivialProducer.h"
#include "L1TriggerConfig/L1GtConfigProducers/interface/L1GtPrescaleFactorsTechTrigTrivialProducer.h"

#include "L1TriggerConfig/L1GtConfigProducers/interface/L1GtTriggerMaskAlgoTrigTrivialProducer.h"
#include "L1TriggerConfig/L1GtConfigProducers/interface/L1GtTriggerMaskTechTrigTrivialProducer.h"

#include "L1TriggerConfig/L1GtConfigProducers/interface/L1GtTriggerMaskVetoAlgoTrigTrivialProducer.h"
#include "L1TriggerConfig/L1GtConfigProducers/interface/L1GtTriggerMaskVetoTechTrigTrivialProducer.h"

//
#include "L1TriggerConfig/L1GtConfigProducers/interface/L1GtBoardMapsTrivialProducer.h"
#include "L1TriggerConfig/L1GtConfigProducers/interface/L1GtPsbSetupTrivialProducer.h"
#include "L1TriggerConfig/L1GtConfigProducers/interface/L1GtTriggerMenuXmlProducer.h"

#include "L1TriggerConfig/L1GtConfigProducers/interface/L1GtStableParametersTester.h"
#include "L1TriggerConfig/L1GtConfigProducers/interface/L1GtParametersTester.h"

#include "L1TriggerConfig/L1GtConfigProducers/interface/L1GtPrescaleFactorsAndMasksTester.h"

#include "L1TriggerConfig/L1GtConfigProducers/interface/L1GtBoardMapsTester.h"
#include "L1TriggerConfig/L1GtConfigProducers/interface/L1GtPsbSetupTester.h"
#include "L1TriggerConfig/L1GtConfigProducers/interface/L1GtTriggerMenuTester.h"

#include "L1TriggerConfig/L1GtConfigProducers/interface/L1GtVhdlWriter.h"

DEFINE_FWK_EVENTSETUP_MODULE(L1GtStableParametersTrivialProducer);
DEFINE_FWK_EVENTSETUP_MODULE(L1GtParametersTrivialProducer);

DEFINE_FWK_EVENTSETUP_MODULE(L1GtPrescaleFactorsAlgoTrigTrivialProducer);
DEFINE_FWK_EVENTSETUP_MODULE(L1GtPrescaleFactorsTechTrigTrivialProducer);

DEFINE_FWK_EVENTSETUP_MODULE(L1GtTriggerMaskAlgoTrigTrivialProducer);
DEFINE_FWK_EVENTSETUP_MODULE(L1GtTriggerMaskTechTrigTrivialProducer);

DEFINE_FWK_EVENTSETUP_MODULE(L1GtTriggerMaskVetoAlgoTrigTrivialProducer);
DEFINE_FWK_EVENTSETUP_MODULE(L1GtTriggerMaskVetoTechTrigTrivialProducer);

//
DEFINE_FWK_EVENTSETUP_MODULE(L1GtBoardMapsTrivialProducer);
DEFINE_FWK_EVENTSETUP_MODULE(L1GtPsbSetupTrivialProducer);
DEFINE_FWK_EVENTSETUP_MODULE(L1GtTriggerMenuXmlProducer);

DEFINE_FWK_MODULE(L1GtStableParametersTester);
DEFINE_FWK_MODULE(L1GtParametersTester);

DEFINE_FWK_MODULE(L1GtPrescaleFactorsAndMasksTester);

DEFINE_FWK_MODULE(L1GtBoardMapsTester);
DEFINE_FWK_MODULE(L1GtPsbSetupTester);
DEFINE_FWK_MODULE(L1GtTriggerMenuTester);
DEFINE_FWK_MODULE(L1GtVhdlWriter);
