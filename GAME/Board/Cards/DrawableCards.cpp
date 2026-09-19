
#include "DrawableCards.h"

//struct   StructName:    Name;                  Description:                     Effect:    Amount:   Position
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", MovePlayer, 200};
ChanceCard Positive_BankError{"Bank error in favor", "a bank error gains you $100", EditMoney, 100};
ChanceCard Negative_BankError{"Bank error Mistake", "a bank error costs you $100", EditMoney, -100};
ChanceCard JailSentence{"Tax Evasion Gone Woof", "Your Dog forgot to file your Taxes, pay a $25 fee & go to jail", MovePlayer, -25, /*fil in jail pos*/};
ChanceCard TaskFailedSuccessfully{"Task Failed Successfully", "Your dog dug up a valuable gem worth &450, but the IRS remembers u exist", EditMoney, 250};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", MovePlayer};
ChanceCard MoveToStart{"Move To Start", "Move forward to start & collect $200", MovePlayer};

ChanceCard DrawChanceCard()
{

}