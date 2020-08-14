package com.ziroby.dmassist.server.model;

import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Getter;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;


public class User {
    @Getter
    private final String userName;

    @JsonIgnore
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

    public Battle getBattle(int battleNum) {
        return battles.get(battleNum);
    }

    @JsonProperty("battles")
    public Collection<Battle> getBattlesAsList() {
        return battles.values();
    }
}
