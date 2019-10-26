package com.fp;

import com.ericsson.otp.erlang.*;

import java.io.IOException;

public class Main {
    public static void main(String[] args) {

        /*ErlangNode initNode = new ErlangNode("i", "init@testerPC", "lab2", "main_p");
        initNode.start();*/



        /*ErlangNode gmNode = new ErlangNode("gm", "manager@testerPC", "lab2", "gm_p");
        gmNode.start();

        ErlangNode playerNode = new ErlangNode("p", "player@testerPC", "lab2", "p_p");
        playerNode.start();

        ErlangNode rollNode = new ErlangNode("r", "roll@testerPC", "lab2", "r_p");
        rollNode.start();

        ErlangNode enemyNode = new ErlangNode("e", "enemy@testerPC", "lab2", "e_p");
        enemyNode.start();

        InitNode initNode = new InitNode("init");
        initNode.start();*/

        MainForm form = new MainForm();
    }
}
