//
//  test_gai.cpp
//  unittests
//
//  Created by Nathan Holmberg on 25/03/13.
//  Copyright (c) 2013 nshgraph. All rights reserved.
//

#include "gtest/gtest.h"

#include "GAI.h"



TEST( GAITest, create_interface )
{
    const std::string product_name = "test_product";
    const std::string product_name2 = "test_product2";
    const std::string version = "1.0.0";
    const std::string data_store_path = "test.db";
    
    // create instance 1
    GAI::Analytics* gai = GAI::Analytics::sharedInstance( product_name, data_store_path );
    
    // create instance 2
    GAI::Analytics* gai2 = GAI::Analytics::sharedInstance( product_name, data_store_path );
    
    // should be the same
    EXPECT_EQ( gai, gai2 );
    
    // should have the correct product name
    EXPECT_EQ(product_name,gai->getProductName());
    
    // should be able to set the product name
    gai->setProductName( product_name2 );
    EXPECT_EQ(product_name2,gai->getProductName());
    
    // should be able to set the version
    gai->setVersion( version );
    EXPECT_EQ(version,gai->getVersion());
    
    // should be able to set the debug state
    gai->setDebug( true );
    EXPECT_TRUE(gai->isDebug());
    gai->setDebug( false );
    EXPECT_FALSE(gai->isDebug());
    
    // should be able to set opt out
    gai->setOptOut( true );
    EXPECT_TRUE(gai->isOptOut());
    gai->setOptOut( false );
    EXPECT_FALSE(gai->isOptOut());
    
    // should be able to set dispatch interval
    gai->setDispatchInterval( 20.0 );
    EXPECT_EQ(20.0,gai->getDispatchInterval());
    gai->setDispatchInterval( 120.0 );
    EXPECT_EQ(120.0,gai->getDispatchInterval());
}


TEST( GAITest, create_trackers )
{
    const std::string product_name = "test_product";
    const std::string data_store_path = "test.db";
    const std::string tracker_id1 = "test_tracker1";
    const std::string tracker_id2 = "test_tracker2";
    
    // create instance 1
    GAI::Analytics* gai = GAI::Analytics::sharedInstance( product_name, data_store_path );
    
    // should start without a default tracker
    EXPECT_TRUE( gai->getDefaultTracker() == NULL);
    
    // shouldn't be able to set the default tracker to just anything
    int test = 0;
    EXPECT_FALSE( gai->setDefaultTracker((GAI::Tracker*)&test) );
    EXPECT_TRUE( gai->getDefaultTracker() == NULL);
    
    // should be able to create a tracker with a given id
    GAI::Tracker* tracker1 = gai->createTracker( tracker_id1 );
    
    // should be able to create a second, different tracker if using a different id
    GAI::Tracker* tracker2 = gai->createTracker( tracker_id2 );
    
    EXPECT_NE( tracker1, tracker2 );
    
    // should be able to retrieve the same tracker with the same id
    GAI::Tracker* tracker3 = gai->createTracker( tracker_id1 );
    
    EXPECT_EQ( tracker1, tracker3 );
    
    // should be able to remove a tracker with a given id
    gai->removeTracker(tracker_id1 );
    tracker3 = gai->createTracker( tracker_id1 );
    
    EXPECT_NE( tracker1, tracker3 );
    
    // should be able to set the default tracker with one of these
    EXPECT_TRUE( gai->setDefaultTracker(tracker3) );
    EXPECT_TRUE( gai->getDefaultTracker() == tracker3);

    
}
