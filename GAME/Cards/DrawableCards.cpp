
#include "DrawableCards.h"
#include "GameState.h"
#include "UI-Helpers.h"
#include "logger-manager.h"

#include <iostream>
#include <vector>
#include <random>
#include <QTimer>
#include <fstream>

// Name, description, effect, money amount, destination, Chance, Community Chest.
Card MoveToStart{"Move To Start", "Move forward to start & collect $200", EffectType::MovePlayer, 200, 0, true, false};
Card Positive_BankError{"Bank Error in Your Favor", "A bank error gains you $100", EffectType::EditMoney, 100, 0, false, true};
Card Negative_BankError{"Bank Error Correction", "A bank error costs you $100", EffectType::EditMoney, -100, 0, false, true};
Card JailSentence{"Tax Evasion Gone Woof", "Your dog forgot to file your taxes. Pay $25 and go to jail", EffectType::MovePlayer, -25, 10, true, false};
Card TaskFailedSuccessfully{"Task Failed Successfully", "Your dog dug up a gem worth $450, but the IRS wants half. Collect $225", EffectType::EditMoney, 225, 0, true, false};
Card SouthboundTrain{"Southbound Train", "Advance to South Station", EffectType::MovePlayer, 0, 5, true, false};
Card RoyalInvitation{"Royal Invitation", "Advance to Royal Avenue", EffectType::MovePlayer, 0, 39, true, false};
Card SpeedingFine{"Speeding Fine", "Your dog chased a car and you got the ticket. Pay $50", EffectType::EditMoney, -50, 0, true, false};
Card LostWallet{"Lost Wallet", "You lost your wallet at the station. Lose $75", EffectType::EditMoney, -75, 0, true, false};
Card TreasureMap{"Treasure Map", "Your questionable treasure map actually worked. Collect $150", EffectType::EditMoney, 150, 0, true, false};
Card StockSale{"Sale of Stock", "From selling stock, you earned $150", EffectType::EditMoney, 150, 0, false, true};
Card DoctorFee{"Doctor's Fee", "Time for your annual checkup. Pay $50", EffectType::EditMoney, -50, 0, false, true};
Card TaxRefund{"Tax Refund", "Your paperwork finally paid off. Collect $100", EffectType::EditMoney, 100, 0, false, true};
Card PetShowPrize{"Pet Show Prize", "Your dog won the neighborhood pet show. Collect $50", EffectType::EditMoney, 50, 0, false, true};
Card RoofRepairs{"Roof Repairs", "That suspicious dripping needs fixing. Pay $125", EffectType::EditMoney, -125, 0, false, true};
Card BirthdayGift{"Birthday Gift", "A relative sent you birthday money. Collect $100", EffectType::EditMoney, 100, 0, false, true};

std::vector<Card> SetupCards()
{
    return {
        MoveToStart,
        Positive_BankError,
        Negative_BankError,
        JailSentence,
        TaskFailedSuccessfully,
        SouthboundTrain,
        RoyalInvitation,
        SpeedingFine,
        LostWallet,
        TreasureMap,
        StockSale,
        DoctorFee,
        TaxRefund,
        PetShowPrize,
        RoofRepairs,
        BirthdayGift
    };
}

void FilterCards(GameState& game, std::vector<Card>& cards)
{
    std::vector<Card> CommunityChests;
    std::vector<Card> ChanceCards;
    std::vector<Card> ErrorType;

    for(Card card : cards)
    {
        if(card.IsChanceCard){ ChanceCards.push_back(card); }
        if(card.IsCommunityChest){ ErrorType.push_back(card); }//
        else{ ErrorType.push_back(card); }
    }

    if(ErrorType.size() > 0)
    {
        LogLineAppend("\nCARDTYPE ERRORS:\n");
        for(Card card : ErrorType)
        {
            LogLineAppend(card.Name);
            LogLineAppend(card.Description);
            //LogLineAppend("\n");
        }
        LogLineAppend("\nEND OF CARDTYPE ERRORS:\n");
    }

    game.ChanceCards = ChanceCards;
    game.CommunityChests = CommunityChests;
}

Card DrawCard(std::vector<Card>& Cards)
{
    std::random_device random;
    std::mt19937 gen(random());
    std::uniform_int_distribution<> dist(0, static_cast<int>(Cards.size()) - 1);

    int rand_int = dist(gen);

    return Cards[rand_int];
}



void ApplyCardEffect(GameState& game, Ui::MainWindow& ui, Card& chance)
{
    Player& CurrentPlayer = game.Players[game.CurrentPlayerIndex];

    //update ui
    UpdateCard(game, ui, chance);

    switch(chance.Effect)
    {
        case EffectType::EditMoney:
            CurrentPlayer.Money += chance.MoneyAmount;
            break;
        case EffectType::MovePlayer:
            CurrentPlayer.Position = chance.SetPlayerPosition;
            break;
        case EffectType::SummonWeather:
            break;
        case EffectType::HouseMarketCrash:
            break;
        case EffectType::ExtremeInflation:
            break;
        
        default:
            std::cerr << "Unhandled effect-type! File: " << __FILE__ << " Line: " << __LINE__ << std::endl;
            break;
    }
    QTimer::singleShot(10000, [&]()
    { 
        ui.chanceText->setText(QString::fromStdString(""));
    });
}