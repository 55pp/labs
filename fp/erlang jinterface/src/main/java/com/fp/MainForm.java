package com.fp;

import com.ericsson.otp.erlang.OtpErlangTuple;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MainForm {
    private JFrame frame;
    private JButton button1;
    private JTextField textField1;

    public MainForm()
    {
        frame = new JFrame();
        textField1 = new JTextField();
        textField1.setSize(100, 50);
        button1 = new JButton("Start");
        button1.setSize(100, 50);

        ErlangNode gmNode = new ErlangNode("gm", "manager@testerPC", "lab2", "gm_p");
        gmNode.start();

        ErlangNode playerNode = new ErlangNode("p", "player@testerPC", "lab2", "p_p");
        playerNode.start();

        ErlangNode rollNode = new ErlangNode("r", "roll@testerPC", "lab2", "r_p");
        rollNode.start();

        ErlangNode enemyNode = new ErlangNode("e", "enemy@testerPC", "lab2", "e_p");
        enemyNode.start();

        final InitNode initNode = new InitNode("init");


        button1.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent actionEvent) {
                OtpErlangTuple tuple = initNode.invoke();
                String stat = tuple.elementAt(1).toString();
                String score = tuple.elementAt(2).toString();
                textField1.setText(stat + " " + score);
            }
        });

        frame.add(textField1);
        frame.add(button1, BorderLayout.WEST);
        frame.setSize(300, 75);
        frame.setVisible(true);
    }
}
