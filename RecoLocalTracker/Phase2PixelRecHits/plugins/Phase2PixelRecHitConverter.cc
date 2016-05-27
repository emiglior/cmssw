/** Phase2PixelRecHitConverter.cc
 * ------------------------------------------------------
 * Description:  see Phase2PixelCPERecHitConverter.h
 * Authors:  P. Maksimovic (JHU), V.Chiochia (Uni Zurich)
 * History: Feb 27, 2006 -  initial version
 *          May 30, 2006 -  edm::DetSetVector and edm::Ref
 *          Aug 30, 2007 -  edmNew::DetSetVector
*			Jan 31, 2008 -  change to use Lorentz angle from DB (Lotte Wilke)
 * ------------------------------------------------------
 */

// Our own stuff
#include "RecoLocalTracker/Phase2PixelRecHits/interface/Phase2PixelRecHitConverter.h"

// Geometry
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetUnit.h"

// Data Formats
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/DetSet2RangeMap.h"


// STL
#include <vector>
#include <memory>
#include <string>
#include <iostream>

// MessageLogger
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "RecoLocalTracker/Records/interface/TkPixelCPERecord.h"

#include "FWCore/Framework/interface/MakerMacros.h"

using namespace std;

  //---------------------------------------------------------------------------
  //!  Constructor: set the ParameterSet and defer all thinking to setupCPE().
  //---------------------------------------------------------------------------
  Phase2PixelRecHitConverter::Phase2PixelRecHitConverter(edm::ParameterSet const& conf) 
    : 
    conf_(conf),
    src_( conf.getParameter<edm::InputTag>( "src" ) ),
    tphase2PixelCluster(consumes< edmNew::DetSetVector<Phase2PixelCluster> >( src_)) {
    //--- Declare to the EDM what kind of collections we will be making.
    produces<Phase2PixelRecHitCollection>();
    
  }
  
  // Destructor
  Phase2PixelRecHitConverter::~Phase2PixelRecHitConverter() 
  { 
  }  
  
  //---------------------------------------------------------------------------
  //! The "Event" entrypoint: gets called by framework for every event
  //---------------------------------------------------------------------------
  void Phase2PixelRecHitConverter::produce(edm::Event& e, const edm::EventSetup& es)
  {

    // Step A.1: get input data
    edm::Handle< edmNew::DetSetVector<Phase2PixelCluster> > input;
    e.getByToken( tphase2PixelCluster, input);
    
    // Step A.2: get event setup
    edm::ESHandle<TrackerGeometry> geom;
    es.get<TrackerDigiGeometryRecord>().get( geom );

    // Step B: create empty output collection
    std::auto_ptr<Phase2PixelRecHitCollectionNew> output(new Phase2PixelRecHitCollectionNew);
    
    // Step B*: create CPE
    edm::ESHandle<Phase2PixelClusterParameterEstimator> hCPE;
    std::string cpeName_ = conf_.getParameter<std::string>("CPE");
    es.get<TkPixelCPERecord>().get(cpeName_,hCPE);
    cpe_ = dynamic_cast< const Phase2PixelCPEBase* >(&(*hCPE));
    
    // Step C: Iterate over DetIds and invoke the strip CPE algorithm
    // on each DetUnit

    run( input, *output, geom );

    output->shrink_to_fit();
    e.put(output);

  }

  //---------------------------------------------------------------------------
  //!  Iterate over DetUnits, then over Clusters and invoke the CPE on each,
  //!  and make a RecHit to store the result.
  //!  New interface reading DetSetVector by V.Chiochia (May 30th, 2006)
  //---------------------------------------------------------------------------
  void Phase2PixelRecHitConverter::run(edm::Handle<edmNew::DetSetVector<Phase2PixelCluster> >  inputhandle,
				   Phase2PixelRecHitCollectionNew &output,
				   edm::ESHandle<TrackerGeometry> & geom) {
    if ( ! cpe_ ) 
      {
	edm::LogError("Phase2PixelRecHitConverter") << " at least one CPE is not ready -- can't run!";
	// TO DO: throw an exception here?  The user may want to know...
	assert(0);
	return;   // clusterizer is invalid, bail out
      }
    
    int numberOfDetUnits = 0;
    int numberOfClusters = 0;
    
    const edmNew::DetSetVector<Phase2PixelCluster>& input = *inputhandle;
    
    edmNew::DetSetVector<Phase2PixelCluster>::const_iterator DSViter=input.begin();
    
    for ( ; DSViter != input.end() ; DSViter++) {
      numberOfDetUnits++;
      unsigned int detid = DSViter->detId();
      DetId detIdObject( detid );  
      const GeomDetUnit * genericDet = geom->idToDetUnit( detIdObject );
      const PixelGeomDetUnit * pixDet = dynamic_cast<const PixelGeomDetUnit*>(genericDet);
      assert(pixDet); 
      Phase2PixelRecHitCollectionNew::FastFiller recHitsOnDetUnit(output,detid);
      
      edmNew::DetSet<Phase2PixelCluster>::const_iterator clustIt = DSViter->begin(), clustEnd = DSViter->end();
      
      for ( ; clustIt != clustEnd; clustIt++) {
	numberOfClusters++;
	std::tuple<LocalPoint, LocalError,SiPixelRecHitQuality::QualWordType> tuple = cpe_->getParameters( *clustIt, *genericDet );
	LocalPoint lp( std::get<0>(tuple) );
	LocalError le( std::get<1>(tuple) );
        SiPixelRecHitQuality::QualWordType rqw( std::get<2>(tuple) );
	// Create a persistent edm::Ref to the cluster
	edm::Ref< edmNew::DetSetVector<Phase2PixelCluster>, Phase2PixelCluster > cluster = edmNew::makeRefTo( inputhandle, clustIt);
	// Make a RecHit and add it to the DetSet
	// old : recHitsOnDetUnit.push_back( new Phase2PixelRecHit( lp, le, detIdObject, &*clustIt) );
	Phase2PixelRecHit hit( lp, le, *genericDet, cluster);
	// 
	// Now save it =================
	recHitsOnDetUnit.push_back(hit);
	// =============================

	// std::cout << "Phase2PixelRecHitConverterVI " << numberOfClusters << ' '<< lp << " " << le << std::endl;
      } //  <-- End loop on Clusters
	

      //  LogDebug("Phase2PixelRecHitConverter")
      //std::cout << "Phase2PixelRecHitConverterVI "
	//	<< " Found " << recHitsOnDetUnit.size() << " RecHits on " << detid //;
	//	<< std::endl;
      
      
    } //    <-- End loop on DetUnits
    
    //    LogDebug ("Phase2PixelRecHitConverter") 
    //  std::cout << "Phase2PixelRecHitConverterVI "
    //  << cpeName_ << " converted " << numberOfClusters 
    //  << " Phase2PixelClusters into Phase2PixelRecHits, in " 
    //  << numberOfDetUnits << " DetUnits." //; 
    //  << std::endl;
	
  }

DEFINE_FWK_MODULE(Phase2PixelRecHitConverter);
