package com.fp;

import com.ericsson.otp.erlang.*;

import java.io.IOException;
import java.util.Arrays;

public class InitNode extends Thread {

    private OtpNode node;
    private OtpMbox mail;
    private OtpErlangPid managerPid = null;

    public InitNode(String nodeName)
    {
        try {
            this.node = new OtpNode(nodeName);
            this.mail = this.node.createMbox();
            this.node.registerName("main", this.mail);
            //this.node.setCookie("java");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void waitPid(String fullNodeName, String nodeName)
    {

        while(!node.ping(fullNodeName, 1000))
        {}

        System.out.println("pong");

        try {
            OtpSelf self = new OtpSelf("self");
            OtpPeer peer = new OtpPeer(fullNodeName);
            OtpConnection connection = self.connect(peer);
            connection.sendRPC("global", "whereis_name", new OtpErlangAtom[]{new OtpErlangAtom(nodeName)});
            OtpErlangObject res = connection.receiveRPC();
            System.out.println(res);
            managerPid = (OtpErlangPid) res;
        } catch (IOException e) {
            e.printStackTrace();
        } catch (OtpAuthException e) {
            e.printStackTrace();
        } catch (OtpErlangExit otpErlangExit) {
            otpErlangExit.printStackTrace();
        }


        /*System.out.println(Arrays.toString(node.getNames()));

        do {
            pid = node.whereis(nodeName);
        }while(pid == null);

        System.out.println(pid);*/
    }

    public OtpErlangTuple invoke()
    {
        if(managerPid == null) {
            waitPid("manager@testerPC", "manager");
        }
        OtpErlangTuple tuple = new OtpErlangTuple(new OtpErlangObject[] { new OtpErlangAtom("m_start"), mail.self()});
        mail.send(managerPid, tuple);

        OtpErlangTuple res = null;

        try {
            res = (OtpErlangTuple)mail.receive();
            System.out.println(res);
        } catch (OtpErlangExit otpErlangExit) {
            otpErlangExit.printStackTrace();
        } catch (OtpErlangDecodeException e) {
            e.printStackTrace();
        }

        return res;
    }

    public void run()
    {
        if(managerPid == null) {
            waitPid("manager@testerPC", "manager");
        }
        OtpErlangTuple tuple = new OtpErlangTuple(new OtpErlangObject[] { new OtpErlangAtom("m_start"), mail.self()});
        mail.send(managerPid, tuple);
        //mail.send("manager", "manager@testerPC", tuple);

        try {
            OtpErlangTuple res = (OtpErlangTuple)mail.receive();
            System.out.println(res);
        } catch (OtpErlangExit otpErlangExit) {
            otpErlangExit.printStackTrace();
        } catch (OtpErlangDecodeException e) {
            e.printStackTrace();
        }
    }
}
