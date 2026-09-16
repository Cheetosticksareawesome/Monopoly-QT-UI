#include "board.h"

Board CreateBoard()
{
    Board board{};
    BoardSpace Rest{"Rest", SpaceType::Rest};

    BoardSpace Go{"GO", SpaceType::Go};
    BoardSpace Oak_st{"Oak Street", SpaceType::Property};
    BoardSpace CommunityChest{"Community Chest", SpaceType::Rest};
    BoardSpace Pine_st{"Pine Street", SpaceType::Property};
    BoardSpace IncomeTax{"Income Tax", SpaceType::Rest};
    BoardSpace SouthStation{"South Station", SpaceType::Property};
    BoardSpace Birch_st{"Birch Street", SpaceType::Property};
    BoardSpace Chance{"Chance", SpaceType::Rest};
    BoardSpace Maple_st{"Maple Street", SpaceType::Property};
    BoardSpace Cedar_st{"Cedar Street", SpaceType::Property};
    BoardSpace Jail{"JAIL / VISITING", SpaceType::Rest};
    BoardSpace Rose_st{"Rose Street", SpaceType::Property};
    BoardSpace ElectricCompany{"Electric Company", SpaceType::Property};
    BoardSpace Tulip_st{"Tulip Street", SpaceType::Property};
    BoardSpace Lily_st{"Lily Street", SpaceType::Property};
    BoardSpace WestStation{"West Station", SpaceType::Property};
    BoardSpace Orange_st{"Orange Street", SpaceType::Property};
    BoardSpace Peach_st{"Peach Street", SpaceType::Property};
    BoardSpace Apricot_st{"Apricot Street", SpaceType::Property};
    BoardSpace FreeParking{"FREE PARKING", SpaceType::Rest};
    BoardSpace Ruby_st{"Ruby Street", SpaceType::Property};
    BoardSpace Scarlet_st{"Scarlet Street", SpaceType::Property};
    BoardSpace Crimson_st{"Crimson Street", SpaceType::Property};
    BoardSpace NorthStation{"North Station", SpaceType::Property};
    BoardSpace Sunflower_st{"Sunflower Street", SpaceType::Property};
    BoardSpace Daffodil_st{"Daffodil Street", SpaceType::Property};
    BoardSpace WaterWorks{"Water Works", SpaceType::Property};
    BoardSpace Marigold_st{"Marigold Street", SpaceType::Property};
    BoardSpace GoToJail{"GO TO JAIL", SpaceType::Rest};
    BoardSpace Forest_st{"Forest Street", SpaceType::Property};
    BoardSpace Willow_st{"Willow Street", SpaceType::Property};
    BoardSpace Meadow_st{"Meadow Street", SpaceType::Property};
    BoardSpace EastStation{"East Station", SpaceType::Property};
    BoardSpace Ocean_ave{"Ocean Avenue", SpaceType::Property};
    BoardSpace LuxuryTax{"Luxury Tax", SpaceType::Rest};
    BoardSpace Royal_ave{"Royal Avenue", SpaceType::Property};

    // Special spaces use Rest until their rules are implemented.
    board.Spaces.resize(40, Rest);
    board.Spaces[0] = Go;
    board.Spaces[1] = Oak_st;
    board.Spaces[2] = CommunityChest;
    board.Spaces[3] = Pine_st;
    board.Spaces[4] = IncomeTax;
    board.Spaces[5] = SouthStation;
    board.Spaces[6] = Birch_st;
    board.Spaces[7] = Chance;
    board.Spaces[8] = Maple_st;
    board.Spaces[9] = Cedar_st;
    board.Spaces[10] = Jail;
    board.Spaces[11] = Rose_st;
    board.Spaces[12] = ElectricCompany;
    board.Spaces[13] = Tulip_st;
    board.Spaces[14] = Lily_st;
    board.Spaces[15] = WestStation;
    board.Spaces[16] = Orange_st;
    board.Spaces[17] = Peach_st;
    board.Spaces[18] = CommunityChest;
    board.Spaces[19] = Apricot_st;
    board.Spaces[20] = FreeParking;
    board.Spaces[21] = Ruby_st;
    board.Spaces[22] = Chance;
    board.Spaces[23] = Scarlet_st;
    board.Spaces[24] = Crimson_st;
    board.Spaces[25] = NorthStation;
    board.Spaces[26] = Sunflower_st;
    board.Spaces[27] = Daffodil_st;
    board.Spaces[28] = WaterWorks;
    board.Spaces[29] = Marigold_st;
    board.Spaces[30] = GoToJail;
    board.Spaces[31] = Forest_st;
    board.Spaces[32] = Willow_st;
    board.Spaces[33] = CommunityChest;
    board.Spaces[34] = Meadow_st;
    board.Spaces[35] = EastStation;
    board.Spaces[36] = Chance;
    board.Spaces[37] = Ocean_ave;
    board.Spaces[38] = LuxuryTax;
    board.Spaces[39] = Royal_ave;

    return board;
}
