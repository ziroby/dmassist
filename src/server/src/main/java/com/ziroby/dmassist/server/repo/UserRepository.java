package com.ziroby.dmassist.server.repo;

import com.ziroby.dmassist.model.EnhancedEntityList;
import com.ziroby.dmassist.server.exception.DuplicateUserNameException;
import com.ziroby.dmassist.server.model.Battle;
import com.ziroby.dmassist.server.model.User;
import org.springframework.stereotype.Component;

import java.util.*;

@Component
public class UserRepository {

    private final Map<String, User> userMap = new HashMap<>();

    public User createUser(String userName) {
        if (userMap.containsKey(userName)) {
            throw new DuplicateUserNameException(String.format("Duplicate username: %s", userName));
        }

        User user = new User(userName);
        userMap.put(userName, user);

        return user;
    }

    public Collection<Battle> getUserBattles(String userName) {
        User user = getUser(userName);
        return user.getBattlesAsList();
    }

    public User getUser(String userName) {
        return userMap.get(userName);
    }

    public Battle createUserBattle(String userName) {
        User user = getUser(userName);
        Battle battle = new Battle(new EnhancedEntityList());
        user.addBattle(battle);
        return battle;
    }

    public Battle getBattle(String userName, String battleNumString) {
        User user = getUser(userName);
        int battleNum = Integer.parseInt(battleNumString);
        return user.getBattle(battleNum);
    }
}
