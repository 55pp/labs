package com.fp;

import com.ericsson.otp.erlang.*;

import java.io.IOException;

public class ErlangNode extends Thread {

    private String name;
    private String fullRemoteNodeName;
    private String moduleName;
    private String funName;

    private OtpSelf otpSelf;
    private OtpPeer otpPeer;
    private OtpConnection otpConnection;

    public ErlangNode(String name, String fullRemoteNodeName, String moduleName, String funName)
    {
        this.name = name;
        this.fullRemoteNodeName = fullRemoteNodeName;
        this.moduleName = moduleName;
        this.funName = funName;

        try {
            this.otpSelf = new OtpSelf(name);
            this.otpPeer = new OtpPeer(fullRemoteNodeName);
            //this.otpSelf.setCookie("java");

            this.otpConnection = this.otpSelf.connect(this.otpPeer);
        } catch (IOException e) {
            e.printStackTrace();
        } catch (OtpAuthException e) {
            e.printStackTrace();
        }
    }

    public OtpErlangObject invoke()
    {
        OtpErlangObject res = null;
        try {
            otpConnection.sendRPC(moduleName, funName, new OtpErlangList());
            res = otpConnection.receiveRPC();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (OtpErlangExit otpErlangExit) {
            otpErlangExit.printStackTrace();
        } catch (OtpAuthException e) {
            e.printStackTrace();
        }

        return res;
    }

    public void run()
    {
        System.out.println(invoke());
    }
}
