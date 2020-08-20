package com.ziroby.dmassist.server.exception;

import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.ResponseStatus;

@ResponseStatus(value = HttpStatus.BAD_REQUEST)
public class DuplicateUserNameException extends RuntimeException {
    public DuplicateUserNameException(String userName) {
        super(String.format("Duplicate username: %s", userName));
    }
}
