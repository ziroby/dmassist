package com.ziroby.dmassist.server.exception;

import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.ResponseStatus;

@ResponseStatus(value = HttpStatus.NOT_FOUND)
public class UnknownUserException extends RuntimeException {
    public UnknownUserException(String username) {
        super("Unknown user: " + username);
    }

    public UnknownUserException(String username, Throwable cause) {
        super("Unknown user: " + username, cause);
    }
}
