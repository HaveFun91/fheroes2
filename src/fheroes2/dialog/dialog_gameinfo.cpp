/***************************************************************************
 *   fheroes2: https://github.com/ihhub/fheroes2                           *
 *   Copyright (C) 2019 - 2022                                             *
 *                                                                         *
 *   Free Heroes2 Engine: http://sourceforge.net/projects/fheroes2         *
 *   Copyright (C) 2009 by Andrey Afletdinov <fheroes2@gmail.com>          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "agg_image.h"
#include "cursor.h"
#include "dialog.h"
#include "difficulty.h"
#include "game.h"
#include "game_hotkeys.h"
#include "game_over.h"
#include "icn.h"
#include "localevent.h"
#include "maps.h"
#include "player_info.h"
#include "settings.h"
#include "translations.h"
#include "ui_button.h"
#include "ui_dialog.h"
#include "ui_text.h"

namespace
{
    enum GameInfoCoordinates
    {
        SCENARIO_INFO_VALUES_BOX_WIDTH = 80,
        DIALOG_CONTENT_WIDTH = 420,
        SCENARIO_INFO_BOX_RIGHT_MARGIN = 11,
        SCENARIO_INFO_ROW_LEFT_MARGIN = 16,
        // This is a shadow offset from the original ICN::SCENIBKG image.
        DIALOG_SHADOW_OFFSET_X = 16,
        DIALOG_SHADOW_OFFSET_Y = 4,
        DIALOG_BORDER_WIDTH = 18,
        // CALCULATED
        SCENARIO_INFO_ROW_OFFSET = DIALOG_BORDER_WIDTH + SCENARIO_INFO_ROW_LEFT_MARGIN,
        SCENARIO_MAP_DIFFICULTY_OFFSET = SCENARIO_INFO_ROW_OFFSET,
        SCENARIO_GAME_DIFFICULTY_OFFSET = SCENARIO_INFO_ROW_OFFSET + SCENARIO_INFO_VALUES_BOX_WIDTH + SCENARIO_INFO_BOX_RIGHT_MARGIN,
        SCENARIO_RATING_OFFSET = SCENARIO_INFO_ROW_OFFSET + SCENARIO_INFO_VALUES_BOX_WIDTH * 2 + SCENARIO_INFO_BOX_RIGHT_MARGIN * 2,
        SCENARIO_MAP_SIZE_OFFSET = SCENARIO_INFO_ROW_OFFSET + SCENARIO_INFO_VALUES_BOX_WIDTH * 3 + SCENARIO_INFO_BOX_RIGHT_MARGIN * 3,
        PLAYER_INFO_ROW_OFFSET = DIALOG_BORDER_WIDTH + 5,
        CONDITION_LABEL_OFFSET = DIALOG_BORDER_WIDTH + 5,
        CONDITION_LABEL_WIDTH = 80,
        CONDITION_DESCRIPTION_OFFSET = CONDITION_LABEL_OFFSET + CONDITION_LABEL_WIDTH + 10,
        CONDITION_DESCRIPTION_WIDTH = 278,
        CONFIG_BUTTON_OFFSET = CONDITION_LABEL_OFFSET,
        OK_BUTTON_OFFSET = DIALOG_CONTENT_WIDTH/2 - 47,
    };
}

void Dialog::GameInfo()
{
    fheroes2::Display & display = fheroes2::Display::instance();
    Settings & conf = Settings::Get();

    // setup cursor
    const CursorRestorer cursorRestorer( true, Cursor::POINTER );

    const fheroes2::Sprite & box = fheroes2::AGG::GetICN( ICN::SCENIBKG, 0 );

    fheroes2::Point dp( ( display.width() - box.width() ) / 2, ( ( display.height() - box.height() ) / 2 ) );
    fheroes2::Blit( box, display, dp.x, dp.y );

    fheroes2::Point pt( dp.x + DIALOG_SHADOW_OFFSET_X, dp.y );
    fheroes2::Text text;

    text.set( conf.MapsName(), fheroes2::FontType::normalWhite() );
    text.draw( pt.x, pt.y + 32, DIALOG_CONTENT_WIDTH, display );

    text.set( _( "Map\nDifficulty" ), fheroes2::FontType::smallWhite() );
    text.draw( pt.x + SCENARIO_MAP_DIFFICULTY_OFFSET, pt.y + 56, SCENARIO_INFO_VALUES_BOX_WIDTH, display );

    text.set( _( "Game\nDifficulty" ), fheroes2::FontType::smallWhite() );
    text.draw( pt.x + SCENARIO_GAME_DIFFICULTY_OFFSET, pt.y + 56, SCENARIO_INFO_VALUES_BOX_WIDTH, display );

    text.set( _( "Rating" ), fheroes2::FontType::smallWhite() );
    text.draw( pt.x + SCENARIO_RATING_OFFSET, pt.y + 78 - text.height( SCENARIO_INFO_VALUES_BOX_WIDTH ), SCENARIO_INFO_VALUES_BOX_WIDTH, display );

    text.set( _( "Map Size" ), fheroes2::FontType::smallWhite() );
    text.draw( pt.x + SCENARIO_MAP_SIZE_OFFSET, pt.y + 78 - text.height( SCENARIO_INFO_VALUES_BOX_WIDTH ), SCENARIO_INFO_VALUES_BOX_WIDTH, display );

    text.set( Difficulty::String( conf.MapsDifficulty() ), fheroes2::FontType::smallWhite() );
    text.draw( pt.x + SCENARIO_MAP_DIFFICULTY_OFFSET, pt.y + 84, SCENARIO_INFO_VALUES_BOX_WIDTH, display );

    text.set( Difficulty::String( Game::getDifficulty() ), fheroes2::FontType::smallWhite() );
    text.draw( pt.x + SCENARIO_GAME_DIFFICULTY_OFFSET, pt.y + 84, SCENARIO_INFO_VALUES_BOX_WIDTH, display );

    text.set( std::to_string( Game::GetRating() ) + " %", fheroes2::FontType::smallWhite() );
    text.draw( pt.x + SCENARIO_RATING_OFFSET, pt.y + 84, SCENARIO_INFO_VALUES_BOX_WIDTH, display );

    text.set( Maps::SizeString( conf.MapsSize().width ), fheroes2::FontType::smallWhite() );
    text.draw( pt.x + SCENARIO_MAP_SIZE_OFFSET, pt.y + 84, SCENARIO_INFO_VALUES_BOX_WIDTH, display );

    text.set( conf.MapsDescription(), fheroes2::FontType::smallWhite() );
    text.draw( pt.x, pt.y + 107, DIALOG_CONTENT_WIDTH, display );

    text.set( _( "Opponents" ), fheroes2::FontType::smallWhite() );
    text.draw( pt.x, pt.y + 152, DIALOG_CONTENT_WIDTH, display );

    text.set( _( "Class" ), fheroes2::FontType::smallWhite() );
    text.draw( pt.x, pt.y + 229, DIALOG_CONTENT_WIDTH, display );

    Interface::PlayersInfo playersInfo;

    playersInfo.UpdateInfo( conf.GetPlayers(), fheroes2::Point( pt.x + PLAYER_INFO_ROW_OFFSET, pt.y + 165 ),
                            fheroes2::Point( pt.x + PLAYER_INFO_ROW_OFFSET, pt.y + 240 ) );
    playersInfo.RedrawInfo( true );

    text.set( _( "Victory\nConditions" ), fheroes2::FontType::smallWhite() );
    text.draw( pt.x + CONDITION_LABEL_OFFSET, pt.y + 347, CONDITION_LABEL_WIDTH, display );

    text.set( GameOver::GetActualDescription( conf.ConditionWins() ), fheroes2::FontType::smallWhite() );
    text.draw( pt.x + CONDITION_DESCRIPTION_OFFSET, pt.y + 350, CONDITION_DESCRIPTION_WIDTH, display );

    text.set( _( "Loss\nConditions" ), fheroes2::FontType::smallWhite() );
    text.draw( pt.x + CONDITION_LABEL_OFFSET, pt.y + 392, CONDITION_LABEL_WIDTH, display );

    text.set( GameOver::GetActualDescription( conf.ConditionLoss() ), fheroes2::FontType::smallWhite() );
    text.draw( pt.x + CONDITION_DESCRIPTION_OFFSET, pt.y + 398, CONDITION_DESCRIPTION_WIDTH, display );

    fheroes2::Button buttonOk( pt.x + OK_BUTTON_OFFSET, pt.y + 426, ICN::REQUESTS, 1, 2 );
    fheroes2::ButtonSprite buttonCfg
        = fheroes2::makeButtonWithShadow( pt.x + CONFIG_BUTTON_OFFSET, pt.y + 426, fheroes2::AGG::GetICN( ICN::BTNCONFIG, 0 ), fheroes2::AGG::GetICN( ICN::BTNCONFIG, 1 ), display );

    buttonOk.draw();
    buttonCfg.draw();

    display.render();

    LocalEvent & le = LocalEvent::Get();

    // message loop
    while ( le.HandleEvents() ) {
        le.MousePressLeft( buttonOk.area() ) ? buttonOk.drawOnPress() : buttonOk.drawOnRelease();
        le.MousePressLeft( buttonCfg.area() ) ? buttonCfg.drawOnPress() : buttonCfg.drawOnRelease();

        if ( le.MouseClickLeft( buttonOk.area() ) || Game::HotKeyCloseWindow() )
            break;

        if ( le.MouseClickLeft( buttonCfg.area() ) ) {
            Dialog::ExtSettings( true );
            display.render();
        }
        else if ( le.MousePressRight( buttonOk.area() ) ) {
            fheroes2::Text header( _( "Okay" ), fheroes2::FontType::normalYellow() );
            fheroes2::Text body( _( "Exit this menu." ), fheroes2::FontType::normalWhite() );

            fheroes2::showMessage( header, body, 0 );
        }
        else {
            playersInfo.readOnlyEventProcessing();
        }
    }
}
