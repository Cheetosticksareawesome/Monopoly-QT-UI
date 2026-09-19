
#include "DrawableCards.h"

#include <vector>

//struct   StructName:    Name;                  Description:                     Effect:    Amount:   Position
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", EffectType::MovePlayer, 200};
ChanceCard Positive_BankError{"Bank error in favor", "a bank error gains you $100", EffectType::EditMoney, 100};
ChanceCard Negative_BankError{"Bank error Mistake", "a bank error costs you $100", EffectType::EditMoney, -100};
ChanceCard JailSentence{"Tax Evasion Gone Woof", "Your Dog forgot to file your Taxes, pay a $25 fee & go to jail", EffectType::MovePlayer, -25, 10};
ChanceCard TaskFailedSuccessfully{"Task Failed Successfully", "Your dog dug up a valuable gem worth &450, but the IRS wants half", EffectType::EditMoney, 225};

/*
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", EffectType::MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", EffectType::MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", EffectType::MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", EffectType::MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", EffectType::MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", EffectType::MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", EffectType::MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", EffectType::MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", EffectType::MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", EffectType::MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", EffectType::MovePlayer};
*/
//struct       Name:    Name:                  Description:                  Effect:       Money:    SetPlayerPosition
Community_Chest C1{  "Sale of Stock", "from selling stock, you earned $150", EffectType::EditMoney,     150,                       };


std::vector<ChanceCard> SetupChanceCards()
{
    std::vector<ChanceCard> ChanceCards;
    ChanceCards.resize(16);

    ChanceCards.push_back(MoveToStart);
    ChanceCards.push_back(Positive_BankError);
    ChanceCards.push_back(Negative_BankError);
    ChanceCards.push_back(JailSentence);
    ChanceCards.push_back(TaskFailedSuccessfully);

    return ChanceCards;
}

std::vector<Community_Chest> SetupCommunityChests()
{
    std::vector<Community_Chest> Community_Chests;
    Community_Chests.resize(16);

    Community_Chests.push_back(C1);

    return Community_Chests;
}

ChanceCard DrawChanceCard()
{

}