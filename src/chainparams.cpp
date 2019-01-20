// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The BOO developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "base58.h"
#include "chainparams.h"
#include "libzerocoin/Params.h"
#include "net.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of

    (0, uint256("0x2a9a8e74e2033c55680cdc5b09ccee037a88a2e08b268039c9652bd2e479db7b"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
	1547248807, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
	6340        // * estimated number of transactions per day after checkpoint, was 2000
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
	(0, uint256("0xb3440bbdfb35ee92a68511b3941190901d53366ac857d11b0b94c89855db826f"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1544284822,
    0,
    250
};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
	(0, uint256("0xae6014ced0227efea31c2aa439326a728837863955db73c9fc4fbb86a0ee7bb3"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1544284822,
    0,
    100
};
    

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        vReviveRewardAddress = "";
        vTreasuryRewardAddress = "";
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x1a;
        pchMessageStart[1] = 0xbd;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0x46;
        vAlertPubKey = ParseHex("0427032f4aea9ade6b709caa6f302c0850e1ecdc9f4cd2619ef28dcd560afcc65bcd7a97bf58523a450a7c8e6e178c9ced2ed5ff96afd8e88284332a87f18af63f");
        nDefaultPort = 8000;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        bnPOSWorkLimit = ~uint256(0) >> 24; // 1 / 2^24
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60;          // Bamboo: 1 day
        nTargetSpacing = 2 * 60;          // Bamboo: 2 minutes
        nPOSTargetSpacing = 1 * 120;		 // Bamboo: 2 minutes
        nPOSDGWBlock = 201;
        nMaturity = 20;                     // 5 Conf to mature coins
        nMasternodeCountDrift = 20;        //Was 20
        nMasternodeCollateralAmt = 50000; //masternode collateral 5K
        nMaxMoneyOut = 21000000 * COIN;  //21m coins minted

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 1; //Was 999999999
        nZerocoinStartHeight = 201;
        nAccumulatorStartHeight = 1;
        nZerocoinStartTime = 1547262418;
        nBlockEnforceSerialRange = 1;       //Enforce serial range starting this block
        nBlockRecalculateAccumulators = ~1; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = ~1;         //First block that bad serials emerged
        nBlockLastGoodCheckpoint = ~1;      //Last valid accumulator checkpoint

        const char* pszTimestamp = "National Suicide Prevention Hotline 1-800-273-8255";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0431d81512c537c1e8ca5834732355740830cfe266d97ba8af2c0f72828745014f78931b94abd2383aa8ed2f8a1ec633dd902ed01edfe834f20374be4207843b43") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1547262418;
        genesis.nBits = 504365040;
        genesis.nNonce = 1723389;


        hashGenesisBlock = genesis.GetHash();

        //printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        //printf("genesis.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());
        assert(hashGenesisBlock == uint256("0x2a9a8e74e2033c55680cdc5b09ccee037a88a2e08b268039c9652bd2e479db7b"));
        assert(genesis.hashMerkleRoot == uint256("0x598ffdff99e67551b7a05dc08dfafcf2e7a6ecea89f9b369bf830f4b21ff160f"));

        //Teams Seeder
        vSeeds.push_back(CDNSSeedData("boo-01.fatpanda.club", "boo-01.fatpanda.club"));
        vSeeds.push_back(CDNSSeedData("boo-02.fatpanda.club", "boo-02.fatpanda.club"));
        vSeeds.push_back(CDNSSeedData("boo-03.fatpanda.club", "boo-03.fatpanda.club"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 25); //B
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 25); //B
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x27)(0x34).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x36)(0x2C).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "031ec5025db611dacdd8dbfbae8bf1a0c00358d262e98d3816ea8b863c2bd735c3";
        strObfuscationPoolDummyAddress = "XCNAsFGy8k7amqRG26ikKyfVDwK8585Z6b";
        nStartMasternodePayments = 1547262418;

        /** Zerocoin */
        zerocoinModulus = "0xc95577b6dce0049b0a20c779af38079355abadde1a1d80c353f6cb697a7ae5a087bad39caa5798478551d0f9d91e6267716506f32412de1d19d17588765eb9502b85c6a18abdb05791cfd8b734e960281193705eeece210920cc922b3af3ceb178bf12c22eb565d5767fbf19545639be8953c2c38ffad41f3371e4aac750ac2d7bd614b3faabb453081d5d88fdbb803657a980bc93707e4b14233a2358c97763bf28f7c933206071477e8b371f229bc9ce7d6ef0ed7163aa5dfe13bc15f7816348b328fa2c1e69d5c88f7b94cee7829d56d1842d77d7bb8692e9fc7b7db059836500de8d57eb43c345feb58671503b932829112941367996b03871300f25efb5";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * ZCENT;      //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20;      //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100;   //full security level for accumulators
        nZerocoinHeaderVersion = 4;    //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};

std::string CChainParams::GetTreasuryRewardAddressAtHeight(int nHeight) const
{
    return vTreasuryRewardAddress;
}

CScript CChainParams::GetTreasuryRewardScriptAtHeight(int nHeight) const
{
    CBitcoinAddress address(GetTreasuryRewardAddressAtHeight(nHeight).c_str());
    assert(address.IsValid());
    CScript script = GetScriptForDestination(address.Get());
    return script;
}

std::string CChainParams::GetReviveRewardAddressAtHeight(int nHeight) const
{
    return vReviveRewardAddress;
}
CScript CChainParams::GetReviveRewardScriptAtHeight(int nHeight) const
{
    CBitcoinAddress address(GetReviveRewardAddressAtHeight(nHeight).c_str());
    assert(address.IsValid());
    CScript script = GetScriptForDestination(address.Get());
    return script;
}


static CMainParams mainParams;

class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x1d;
        pchMessageStart[1] = 0xba;
        pchMessageStart[2] = 0xc2;
        pchMessageStart[3] = 0x45;
        vAlertPubKey = ParseHex("0431d81512c537c1e8ca5834732355740830cfe266d97ba8af2c0f72828745014f78931b94abd2383aa8ed2f8a1ec633dd902ed01edfe834f20374be4207843b43");
        nDefaultPort = 15521;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Bamboo: 1 day
        nTargetSpacing = 1 * 60;  // Bamboo: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 10;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 21000000 * COIN;
        nZerocoinStartHeight = 201;
        nZerocoinStartTime = 1544297968;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 9891737; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 9891730; //Last valid accumulator checkpoint
        
        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1544145744;
        genesis.nNonce = 54438;

	    hashGenesisBlock = genesis.GetHash();
        
		//printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        //printf("genesis.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());
        assert(hashGenesisBlock == uint256("0xb3440bbdfb35ee92a68511b3941190901d53366ac857d11b0b94c89855db826f"));
        assert(genesis.hashMerkleRoot == uint256("0x598ffdff99e67551b7a05dc08dfafcf2e7a6ecea89f9b369bf830f4b21ff160f"));

        vFixedSeeds.clear();
        vSeeds.clear();
        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet bamboo addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet bamboo script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet bamboo BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet bamboo BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet bamboo BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "030262a2a0679d01ab026d375c42b0a4122477123631b870e09665526c322c8899";
        strObfuscationPoolDummyAddress = "XCNAsFGy8k7amqRG26ikKyfVDwK8585Z6b";
        nStartMasternodePayments = 1544297968;
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x1d;
        pchMessageStart[1] = 0xba;
        pchMessageStart[2] = 0xc2;
        pchMessageStart[3] = 0x45;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 1 * 60; // Bamboo: 1 day
        nTargetSpacing = 1 * 60;        // Bamboo: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1544284822;
        genesis.nBits = 504365040;
        genesis.nNonce = 1311718;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 15222;
        //printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        //printf("genesis.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());
        assert(hashGenesisBlock == uint256("0xae6014ced0227efea31c2aa439326a728837863955db73c9fc4fbb86a0ee7bb3"));
        assert(genesis.hashMerkleRoot == uint256("0x598ffdff99e67551b7a05dc08dfafcf2e7a6ecea89f9b369bf830f4b21ff160f"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18334;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
         case CBaseChainParams::TESTNET:
          return testNetParams;
         case CBaseChainParams::REGTEST:
           return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
