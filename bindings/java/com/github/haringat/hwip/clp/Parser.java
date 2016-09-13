package com.github.haringat.hwip.clp;

import java.util.List;

class Parser {
    private static List<Argument> args;
    public static native void parseCLI();
    public static native void addArg(String[] aliases, String description);
    public static native void addArg(String[] aliases, String description, int argCount);
    public static native void addArg(String name, String description);
    public static native void addArg(String name, String description, int argCount);
}
