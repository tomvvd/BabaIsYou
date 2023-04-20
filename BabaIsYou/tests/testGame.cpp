#include <catch2/catch_test_macros.hpp>
#include "Game.h"

TEST_CASE( "Test of Game") {
    Game game;
    //Position du joueur Baba
    Position posPlayer{9,6};

    SECTION("Test Method simple move(...) : DOWN direction good"){
        game.move(Direction::DOWN);
        Position pos{10,6};
        vector<Entity> entities = game.getBoardEntities(pos);
        bool res{false};
        for (int i = 0; i < entities.size() && !res; ++i) {
            res = entities[i].getType()==EntityType::ELEMENT && entities[i].getNature() == EntityNature::BABA;
        }
        //vérifie que le joueur n'est plus présent à son ancienne position
        vector<Entity> entities2 = game.getBoardEntities(posPlayer);
        bool res2{false};
        for (int i = 0; i < entities2.size() && !res2; ++i) {
            res2 = entities2[i].getType()==EntityType::ELEMENT && entities2[i].getNature() == EntityNature::BABA;
        }
        REQUIRE(res);
        REQUIRE_FALSE(res2);
    }
    SECTION("Test Method simple move(...) : UP direction good"){
        game.move(Direction::UP);
        Position pos{8,6};
        vector<Entity> entities = game.getBoardEntities(pos);
        bool res{false};
        for (int i = 0; i < entities.size() && !res; ++i) {
            res = entities[i].getType()==EntityType::ELEMENT && entities[i].getNature() == EntityNature::BABA;
        }
        //vérifie que le joueur n'est plus présent à son ancienne position
        vector<Entity> entities2 = game.getBoardEntities(posPlayer);
        bool res2{false};
        for (int i = 0; i < entities2.size() && !res2; ++i) {
            res2 = entities2[i].getType()==EntityType::ELEMENT && entities2[i].getNature() == EntityNature::BABA;
        }
        REQUIRE(res);
        REQUIRE_FALSE(res2);
    }
    SECTION("Test Method simple move(...) : LEFT direction good"){
        game.move(Direction::LEFT);
        Position pos{9,5};
        vector<Entity> entities = game.getBoardEntities(pos);
        bool res{false};
        for (int i = 0; i < entities.size() && !res; ++i) {
            res = entities[i].getType()==EntityType::ELEMENT && entities[i].getNature() == EntityNature::BABA;
        }
        //vérifie que le joueur n'est plus présent à son ancienne position
        vector<Entity> entities2 = game.getBoardEntities(posPlayer);
        bool res2{false};
        for (int i = 0; i < entities2.size() && !res2; ++i) {
            res2 = entities2[i].getType()==EntityType::ELEMENT && entities2[i].getNature() == EntityNature::BABA;
        }
        REQUIRE(res);
        REQUIRE_FALSE(res2);
    }
    SECTION("Test Method simple move(...) : RIGHT direction good"){
        game.move(Direction::RIGHT);
        Position pos{9,7};
        vector<Entity> entities = game.getBoardEntities(pos);
        bool res{false};
        for (int i = 0; i < entities.size() && !res; ++i) {
            res = entities[i].getType()==EntityType::ELEMENT && entities[i].getNature() == EntityNature::BABA;
        }
        //vérifie que le joueur n'est plus présent à son ancienne position
        vector<Entity> entities2 = game.getBoardEntities(posPlayer);
        bool res2{false};
        for (int i = 0; i < entities2.size() && !res2; ++i) {
            res2 = entities2[i].getType()==EntityType::ELEMENT && entities2[i].getNature() == EntityNature::BABA;
        }
        REQUIRE(res);
        REQUIRE_FALSE(res2);
    }
    SECTION("Test Method move(...) : rule stop"){
        game.move(Direction::DOWN);
        game.move(Direction::DOWN);
        Position pos{10,6};
        vector<Entity> entities = game.getBoardEntities(pos);
        bool res{false};
        for (int i = 0; i < entities.size() && !res; ++i) {
            res = entities[i].getType()==EntityType::ELEMENT && entities[i].getNature() == EntityNature::BABA;
        }
        //vérifie que le joueur a été bloqué par un mur (WALL IS STOP)
        Position pos2{11,6};
        vector<Entity> entities2 = game.getBoardEntities(pos2);
        bool res2{false};
        for (int i = 0; i < entities2.size() && !res2; ++i) {
            res2 = entities2[i].getType()==EntityType::ELEMENT && entities2[i].getNature() == EntityNature::BABA;
        }
        REQUIRE(res);
        REQUIRE_FALSE(res2);
    }
    SECTION("Test Method move(...) : rule push"){
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        Position pos{9,9};
        vector<Entity> entities = game.getBoardEntities(pos);
        bool res{false};
        for (int i = 0; i < entities.size() && !res; ++i) {
            res = entities[i].getType()==EntityType::ELEMENT && entities[i].getNature() == EntityNature::BABA;
        }
        //vérifie que le rocher n'est plus là (ROCK IS PUSH)
        Position pos2{9,9};
        vector<Entity> entities2 = game.getBoardEntities(pos2);
        bool res2{false};
        for (int i = 0; i < entities2.size() && !res2; ++i) {
            res2 = entities2[i].getType()==EntityType::ELEMENT && entities2[i].getNature() == EntityNature::ROCK;
        }
        //vérifie que le rocher a bien été poussé
        Position pos3{9,10};
        vector<Entity> entities3 = game.getBoardEntities(pos3);
        bool res3{false};
        for (int i = 0; i < entities3.size() && !res3; ++i) {
            res3 = entities3[i].getType()==EntityType::ELEMENT && entities3[i].getNature() == EntityNature::ROCK;
        }
        REQUIRE(res);
        REQUIRE_FALSE(res2);
        REQUIRE(res3);
    }
    SECTION("Test Method move(...) : push whole rule"){
        game.move(Direction::LEFT);
        game.move(Direction::LEFT);
        game.move(Direction::LEFT);
        game.move(Direction::UP);
        game.move(Direction::UP);
        game.move(Direction::UP);
        game.move(Direction::UP);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        Position pos{5,5};
        vector<Entity> entities = game.getBoardEntities(pos);
        bool res{false};
        for (int i = 0; i < entities.size() && !res; ++i) {
            res = entities[i].getType()==EntityType::ELEMENT && entities[i].getNature() == EntityNature::BABA;
        }
        //vérifie que le texte WALL a été poussé
        Position pos2{5,6};
        vector<Entity> entities2 = game.getBoardEntities(pos2);
        bool res2{false};
        for (int i = 0; i < entities2.size() && !res2; ++i) {
            res2 = entities2[i].getType()==EntityType::TEXT && entities2[i].getNature() == EntityNature::WALL;
        }
        //vérifie que le texte IS a été poussé
        Position pos3{5,7};
        vector<Entity> entities3 = game.getBoardEntities(pos3);
        bool res3{false};
        for (int i = 0; i < entities3.size() && !res3; ++i) {
            res3 = entities3[i].getType()==EntityType::TEXT && entities3[i].getNature() == EntityNature::IS;
        }
        //vérifie que le texte STOP a été poussé
        Position pos4{5,8};
        vector<Entity> entities4 = game.getBoardEntities(pos4);
        bool res4{false};
        for (int i = 0; i < entities4.size() && !res4; ++i) {
            res4 = entities4[i].getType()==EntityType::TEXT && entities4[i].getNature() == EntityNature::STOP;
        }
        REQUIRE(res);
        REQUIRE(res2);
        REQUIRE(res3);
        REQUIRE(res4);
    }
    SECTION("Test Method move(...) : rule win"){
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::UP);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::DOWN);
        REQUIRE(game.isLevelOver());
    }
    SECTION("Test Method move(...) : break the rule"){
        game.move(Direction::LEFT);
        game.move(Direction::LEFT);
        game.move(Direction::LEFT);
        game.move(Direction::UP);
        game.move(Direction::UP);
        game.move(Direction::UP);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::UP);
        game.move(Direction::DOWN);
        game.move(Direction::DOWN);
        Position pos{7,5};
        vector<Entity> entities = game.getBoardEntities(pos);
        bool res{false};
        for (int i = 0; i < entities.size() && !res; ++i) {
            res = entities[i].getType()==EntityType::ELEMENT && entities[i].getNature() == EntityNature::BABA;
        }
        //vérifie que le joueur a traversé un mur (WALL IS STOP)
        bool res2{false};
        for (int i = 0; i < entities.size() && !res2; ++i) {
            res2 = entities[i].getType()==EntityType::ELEMENT && entities[i].getNature() == EntityNature::WALL;
        }
        REQUIRE(res);
        REQUIRE(res2);
    }
    SECTION("Test Method move(...) : change the player (FLAG IS YOU"){
        game.move(Direction::LEFT);
        game.move(Direction::LEFT);
        game.move(Direction::LEFT);
        game.move(Direction::DOWN);
        game.move(Direction::DOWN);
        game.move(Direction::DOWN);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::DOWN);
        game.move(Direction::RIGHT);
        game.move(Direction::DOWN);
        game.move(Direction::LEFT);
        game.move(Direction::LEFT);
        game.move(Direction::LEFT);
        game.move(Direction::LEFT);
        game.move(Direction::LEFT);
        game.move(Direction::LEFT);
        game.move(Direction::LEFT);
        game.move(Direction::DOWN);
        game.move(Direction::LEFT);
        game.move(Direction::UP);
        //flag is you
        game.move(Direction::RIGHT);

        //vérifie que le drapeau a bougé
        Position pos{9,14};
        vector<Entity> entities = game.getBoardEntities(pos);
        bool res{false};
        for (int i = 0; i < entities.size() && !res; ++i) {
            res = entities[i].getType()==EntityType::ELEMENT && entities[i].getNature() == EntityNature::FLAG;
        }
        REQUIRE(res);
    }
    SECTION("Test Method move(...) : WALL IS ROCK"){
        game.move(Direction::LEFT);
        game.move(Direction::LEFT);
        game.move(Direction::LEFT);
        game.move(Direction::UP);
        game.move(Direction::UP);
        game.move(Direction::UP);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::UP);
        game.move(Direction::RIGHT);
        game.move(Direction::DOWN);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::UP);
        game.move(Direction::LEFT);
        game.move(Direction::LEFT);
        game.move(Direction::LEFT);
        game.move(Direction::LEFT);
        game.move(Direction::LEFT);
        //les murs sont devenus des rochers

        Position pos{7,6};
        vector<Entity> entities = game.getBoardEntities(pos);
        bool res{false};
        for (int i = 0; i < entities.size() && !res; ++i) {
            res = entities[i].getType()==EntityType::ELEMENT && entities[i].getNature() == EntityNature::ROCK;
        }
        REQUIRE(res);
    }
    SECTION("Test Method simple move(...) : rule sink"){
        game.constructLevel(3);
        game.move(Direction::DOWN);
        game.move(Direction::DOWN);
        //vérifie que la case est vide
        Position pos{9,8};
        vector<Entity> entities = game.getBoardEntities(pos);

        REQUIRE(entities.empty());
    }
    SECTION("Test Method simple move(...) : rule kill"){
        game.constructLevel(4);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        game.move(Direction::RIGHT);
        //vérifie que la case est vide
        Position pos{8,11};
        vector<Entity> entities = game.getBoardEntities(pos);
        bool res{false};
        for (int i = 0; i < entities.size() && !res; ++i) {
            res = entities[i].getType()==EntityType::ELEMENT && entities[i].getNature() == EntityNature::BABA;
        }
        bool res2{false};
        for (int i = 0; i < entities.size() && !res2; ++i) {
            res2 = entities[i].getType()==EntityType::ELEMENT && entities[i].getNature() == EntityNature::LAVA;
        }
        REQUIRE_FALSE(res);
        REQUIRE(res2);
    }
}
