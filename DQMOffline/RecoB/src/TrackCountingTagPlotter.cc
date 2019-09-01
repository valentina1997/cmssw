#include "DQMOffline/RecoB/interface/TrackCountingTagPlotter.h"
#include "DQMOffline/RecoB/interface/Tools.h"

using namespace std;
using namespace RecoBTag;

TrackCountingTagPlotter::TrackCountingTagPlotter(const std::string& tagName,
                                                 const EtaPtBin& etaPtBin,
                                                 const edm::ParameterSet& pSet,
                                                 unsigned int mc,
                                                 bool wf,
                                                 DQMStore::IBooker& ibook)
    : BaseTagInfoPlotter(tagName, etaPtBin),
      mcPlots_(mc),
      nBinEffPur_(pSet.getParameter<int>("nBinEffPur")),
      startEffPur_(pSet.getParameter<double>("startEffPur")),
      endEffPur_(pSet.getParameter<double>("endEffPur")),
      willFinalize_(wf),
      lowerIPSBound(-35.0),
      upperIPSBound(35.0) {
  const std::string dir(theExtensionString.substr(1));
  if (willFinalize_)
    return;

  trkNbr3D = std::make_unique<FlavourHistograms<int>>("selTrksNbr_3D" + theExtensionString,
                                                      "Number of selected tracks for 3D IPS" + theExtensionString,
                                                      31,
                                                      -0.5,
                                                      30.5,
                                                      false,
                                                      true,
                                                      true,
                                                      "b",
                                                      dir,
                                                      mc,
                                                      ibook);

  trkNbr2D = std::make_unique<FlavourHistograms<int>>("selTrksNbr_2D" + theExtensionString,
                                                      "Number of selected tracks for 2D IPS" + theExtensionString,
                                                      31,
                                                      -0.5,
                                                      30.5,
                                                      false,
                                                      true,
                                                      true,
                                                      "b",
                                                      dir,
                                                      mc,
                                                      ibook);

  for (unsigned int i = 1; i <= 4; i++) {
    tkcntHistosSig3D.push_back(std::make_unique<FlavourHistograms<double>>(
        "ips" + std::to_string(i) + "_3D" + theExtensionString,
        "3D Significance of impact parameter " + std::to_string(i) + ". trk",
        50,
        lowerIPSBound,
        upperIPSBound,
        false,
        true,
        true,
        "b",
        dir,
        mc,
        ibook));
  }
  tkcntHistosSig3D.push_back(std::make_unique<FlavourHistograms<double>>("ips_3D" + theExtensionString,
                                                                         "3D Significance of impact parameter",
                                                                         50,
                                                                         lowerIPSBound,
                                                                         upperIPSBound,
                                                                         false,
                                                                         true,
                                                                         true,
                                                                         "b",
                                                                         dir,
                                                                         mc,
                                                                         ibook));

  for (unsigned int i = 1; i <= 4; i++) {
    tkcntHistosSig2D.push_back(std::make_unique<FlavourHistograms<double>>(
        "ips" + std::to_string(i) + "_2D" + theExtensionString,
        "2D Significance of impact parameter " + std::to_string(i) + ". trk",
        50,
        lowerIPSBound,
        upperIPSBound,
        false,
        true,
        true,
        "b",
        dir,
        mc,
        ibook));
  }

  tkcntHistosSig2D.push_back(std::make_unique<FlavourHistograms<double>>("ips_2D" + theExtensionString,
                                                                         "2D Significance of impact parameter",
                                                                         50,
                                                                         lowerIPSBound,
                                                                         upperIPSBound,
                                                                         false,
                                                                         true,
                                                                         true,
                                                                         "b",
                                                                         dir,
                                                                         mc,
                                                                         ibook));
}

TrackCountingTagPlotter::~TrackCountingTagPlotter() {}

void TrackCountingTagPlotter::analyzeTag(const reco::BaseTagInfo* baseTagInfo, double jec, int jetFlavour, float w) {
  const reco::TrackCountingTagInfo* tagInfo = dynamic_cast<const reco::TrackCountingTagInfo*>(baseTagInfo);

  if (!tagInfo) {
    throw cms::Exception("Configuration")
        << "BTagPerformanceAnalyzer: Extended TagInfo not of type TrackCountingTagInfo. " << endl;
  }

  trkNbr3D->fill(jetFlavour, tagInfo->selectedTracks(0), w);
  trkNbr2D->fill(jetFlavour, tagInfo->selectedTracks(1), w);

  for (int n = 0; n != tagInfo->selectedTracks(1) && n != 4; ++n)
    tkcntHistosSig2D[n]->fill(jetFlavour, tagInfo->significance(n, 1), w);
  for (int n = tagInfo->selectedTracks(1); n < 4; ++n)
    tkcntHistosSig2D[n]->fill(jetFlavour, lowerIPSBound - 1.0, w);

  for (int n = 0; n != tagInfo->selectedTracks(0) && n != 4; ++n)
    tkcntHistosSig3D[n]->fill(jetFlavour, tagInfo->significance(n, 0), w);
  for (int n = tagInfo->selectedTracks(0); n < 4; ++n)
    tkcntHistosSig3D[n]->fill(jetFlavour, lowerIPSBound - 1.0, w);

  for (int n = 0; n != tagInfo->selectedTracks(1); ++n)
    tkcntHistosSig2D[4]->fill(jetFlavour, tagInfo->significance(n, 1), w);
  for (int n = 0; n != tagInfo->selectedTracks(0); ++n)
    tkcntHistosSig3D[4]->fill(jetFlavour, tagInfo->significance(n, 0), w);
}

void TrackCountingTagPlotter::finalize(DQMStore::IBooker& ibook, DQMStore::IGetter& igetter_) {
  //
  // final processing:
  // produce the misid. vs. eff histograms
  //
  const std::string dir("TrackCounting" + theExtensionString);

  tkcntHistosSig3D.clear();
  tkcntHistosSig2D.clear();
  effPurFromHistos.clear();

  for (unsigned int i = 2; i <= 3; i++) {
    tkcntHistosSig3D.push_back(std::make_unique<FlavourHistograms<double>>(
        "ips" + std::to_string(i) + "_3D" + theExtensionString,
        "3D Significance of impact parameter " + std::to_string(i) + ". trk",
        50,
        lowerIPSBound,
        upperIPSBound,
        "b",
        dir,
        mcPlots_,
        igetter_));
    effPurFromHistos.push_back(std::make_unique<EffPurFromHistos>(
        *tkcntHistosSig3D.back(), dir, mcPlots_, ibook, nBinEffPur_, startEffPur_, endEffPur_));
  }

  for (unsigned int i = 2; i <= 3; i++) {
    tkcntHistosSig2D.push_back(std::make_unique<FlavourHistograms<double>>(
        "ips" + std::to_string(i) + "_2D" + theExtensionString,
        "2D Significance of impact parameter " + std::to_string(i) + ". trk",
        50,
        lowerIPSBound,
        upperIPSBound,
        "b",
        dir,
        mcPlots_,
        igetter_));
    effPurFromHistos.push_back(std::make_unique<EffPurFromHistos>(
        *tkcntHistosSig2D.back(), dir, mcPlots_, ibook, nBinEffPur_, startEffPur_, endEffPur_));
  }

  for (int n = 0; n != 4; ++n)
    effPurFromHistos[n]->compute(ibook);
}

void TrackCountingTagPlotter::psPlot(const std::string& name) {
  const std::string cName("TrackCountingPlots" + theExtensionString);
  setTDRStyle()->cd();
  TCanvas canvas(cName.c_str(), cName.c_str(), 600, 900);
  canvas.UseCurrentStyle();
  if (willFinalize_) {
    for (int n = 0; n != 2; ++n) {
      canvas.Print((name + cName + ".ps").c_str());
      canvas.Clear();
      canvas.Divide(2, 3);
      canvas.cd(1);
      effPurFromHistos[0 + n]->discriminatorNoCutEffic().plot();
      canvas.cd(2);
      effPurFromHistos[0 + n]->discriminatorCutEfficScan().plot();
      canvas.cd(3);
      effPurFromHistos[0 + n]->plot();
      canvas.cd(4);
      effPurFromHistos[1 + n]->discriminatorNoCutEffic().plot();
      canvas.cd(5);
      effPurFromHistos[1 + n]->discriminatorCutEfficScan().plot();
      canvas.cd(6);
      effPurFromHistos[1 + n]->plot();
    }
    return;
  }

  canvas.Clear();
  canvas.Divide(2, 3);
  canvas.Print((name + cName + ".ps[").c_str());

  canvas.cd(1);
  trkNbr3D->plot();
  canvas.cd(2);
  tkcntHistosSig3D[4]->plot();
  for (int n = 0; n < 4; n++) {
    canvas.cd(3 + n);
    tkcntHistosSig3D[n]->plot();
  }

  canvas.Print((name + cName + ".ps").c_str());
  canvas.Clear();
  canvas.Divide(2, 3);

  canvas.cd(1);
  trkNbr2D->plot();
  canvas.cd(2);
  tkcntHistosSig2D[4]->plot();
  for (int n = 0; n != 4; ++n) {
    canvas.cd(3 + n);
    tkcntHistosSig2D[n]->plot();
  }

  canvas.Print((name + cName + ".ps").c_str());
  canvas.Print((name + cName + ".ps]").c_str());
}

void TrackCountingTagPlotter::epsPlot(const std::string& name) {
  if (willFinalize_) {
    for (int n = 0; n != 4; ++n)
      effPurFromHistos[n]->epsPlot(name);
    return;
  }

  trkNbr2D->epsPlot(name);
  trkNbr3D->epsPlot(name);
  for (int n = 0; n != 5; ++n) {
    tkcntHistosSig2D[n]->epsPlot(name);
    tkcntHistosSig3D[n]->epsPlot(name);
  }
}
