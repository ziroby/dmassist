package com.ziroby.dmassist.server.exception;

public class DuplicateUserNameException extends RuntimeException {
    public DuplicateUserNameException(String s) {
        super(s);
    }
}
