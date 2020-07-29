package com.ziroby.dmassist.server.model;

import lombok.Getter;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

@Getter
public class User {
    private final String userName;

    private final Map<Integer, Battle> battles = new HashMap<>();

    public User(String userName) {
        if (userName == null) {
            throw new NullPointerException();
        }
        this.userName = userName;
    }

    public void addBattle(Battle battle) {
        battles.put(battle.getId(), battle);
    }

    public Battle getBattle(String battleNum) {
        return battles.get(battleNum);
    }

    public Collection<Battle> getBattlesAsList() {
        return battles.values();
    }
}
