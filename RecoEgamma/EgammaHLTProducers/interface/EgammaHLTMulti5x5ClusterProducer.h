#ifndef RecoEcal_EgammaClusterProducers_EgammaHLTMulti5x5ClusterProducer_h_
#define RecoEcal_EgammaClusterProducers_EgammaHLTMulti5x5ClusterProducer_h_

#include <memory>
#include <ctime>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/CaloRecHit/interface/CaloClusterFwd.h"
#include "RecoEcal/EgammaClusterAlgos/interface/Multi5x5ClusterAlgo.h"

#include "DataFormats/L1Trigger/interface/L1EmParticle.h"
#include "DataFormats/L1Trigger/interface/L1EmParticleFwd.h"

#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/Math/interface/RectangularEtaPhiRegion.h"

namespace edm {
  class ConfigurationDescriptions;
}

class EgammaHLTMulti5x5ClusterProducer : public edm::stream::EDProducer<> {
public:
  EgammaHLTMulti5x5ClusterProducer(const edm::ParameterSet& ps);
  ~EgammaHLTMulti5x5ClusterProducer() override;
  void produce(edm::Event&, const edm::EventSetup&) override;
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  bool doBarrel_;
  bool doEndcaps_;
  bool doIsolated_;

  edm::EDGetTokenT<l1extra::L1EmParticleCollection> l1TagIsolated_;
  edm::EDGetTokenT<l1extra::L1EmParticleCollection> l1TagNonIsolated_;
  edm::InputTag barrelHitCollection_;
  edm::InputTag endcapHitCollection_;
  edm::EDGetTokenT<EcalRecHitCollection> barrelHitToken_;
  edm::EDGetTokenT<EcalRecHitCollection> endcapHitToken_;

  std::string barrelClusterCollection_;
  std::string endcapClusterCollection_;

  double l1LowerThr_;
  double l1UpperThr_;
  double l1LowerThrIgnoreIsolation_;

  double regionEtaMargin_;
  double regionPhiMargin_;

  PositionCalc posCalculator_;  // position calculation algorithm
  Multi5x5ClusterAlgo* Multi5x5_p;

  const EcalRecHitCollection* getCollection(edm::Event& evt,
                                            const edm::EDGetTokenT<EcalRecHitCollection>& hitToken) const;

  void clusterizeECALPart(edm::Event& evt,
                          const edm::EventSetup& es,
                          const edm::EDGetTokenT<EcalRecHitCollection>& hitToken,
                          const std::string& clusterCollection,
                          const std::vector<RectangularEtaPhiRegion>& regions,
                          const reco::CaloID::Detectors detector) const;

  void outputValidationInfo(reco::CaloClusterPtrVector& clusterPtrVector);
};
#endif
