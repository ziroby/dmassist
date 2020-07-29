package com.ziroby.dmassist.server.web;

import com.ziroby.dmassist.server.model.Battle;
import com.ziroby.dmassist.server.model.User;

import com.ziroby.dmassist.server.repo.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.Collection;

@RestController
public class UserController {

    @Autowired
    private UserRepository userRepository;

    @PutMapping("/users/{userName}")
    public User newUser(@PathVariable String userName) {
        return userRepository.createUser(userName);
    }

    @GetMapping("/users/{userName}")
    public User getUser(@PathVariable String userName) {
        return userRepository.getUser(userName);
    }

    @GetMapping("/users/{userName}/battles")
    public Collection<Battle> getUserBattles(@PathVariable String userName) {
        return userRepository.getUserBattles(userName);
    }
    @PutMapping("/users/{userName}/battles")
    public Battle createUserBattle(@PathVariable String userName) {
        return userRepository.createUserBattle(userName);
    }
}
