<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_52" />
        <signal name="XLXN_53" />
        <signal name="XLXN_54" />
        <signal name="XLXN_55" />
        <signal name="XLXN_56" />
        <signal name="XLXN_57" />
        <signal name="CLR" />
        <signal name="CLK" />
        <signal name="RD" />
        <signal name="RI" />
        <signal name="AD" />
        <signal name="AI" />
        <signal name="VD" />
        <signal name="VI" />
        <signal name="S1" />
        <signal name="S0" />
        <port polarity="Input" name="CLR" />
        <port polarity="Input" name="CLK" />
        <port polarity="Output" name="RD" />
        <port polarity="Output" name="RI" />
        <port polarity="Output" name="AD" />
        <port polarity="Output" name="AI" />
        <port polarity="Output" name="VD" />
        <port polarity="Output" name="VI" />
        <port polarity="Input" name="S1" />
        <port polarity="Input" name="S0" />
        <blockdef name="fdc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <rect width="256" x="64" y="-320" height="256" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
        </blockdef>
        <blockdef name="control_obras">
            <timestamp>2022-11-29T14:9:44</timestamp>
            <rect width="256" x="64" y="-576" height="576" />
            <line x2="384" y1="-224" y2="-224" x1="320" />
            <line x2="384" y1="-160" y2="-160" x1="320" />
            <line x2="384" y1="-416" y2="-416" x1="320" />
            <line x2="384" y1="-480" y2="-480" x1="320" />
            <line x2="384" y1="-544" y2="-544" x1="320" />
            <line x2="0" y1="-416" y2="-416" x1="64" />
            <line x2="0" y1="-480" y2="-480" x1="64" />
            <line x2="0" y1="-544" y2="-544" x1="64" />
            <line x2="384" y1="-352" y2="-352" x1="320" />
            <line x2="384" y1="-288" y2="-288" x1="320" />
            <line x2="0" y1="-288" y2="-288" x1="64" />
            <line x2="0" y1="-352" y2="-352" x1="64" />
            <line x2="384" y1="-96" y2="-96" x1="320" />
            <line x2="384" y1="-32" y2="-32" x1="320" />
        </blockdef>
        <block symbolname="fdc" name="XLXI_2">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="XLXN_52" name="D" />
            <blockpin signalname="XLXN_55" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_3">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="XLXN_53" name="D" />
            <blockpin signalname="XLXN_56" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_4">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="XLXN_54" name="D" />
            <blockpin signalname="XLXN_57" name="Q" />
        </block>
        <block symbolname="control_obras" name="XLXI_5">
            <blockpin signalname="AD" name="AD" />
            <blockpin signalname="AI" name="AI" />
            <blockpin signalname="XLXN_54" name="D0" />
            <blockpin signalname="XLXN_53" name="D1" />
            <blockpin signalname="XLXN_52" name="D2" />
            <blockpin signalname="XLXN_57" name="Q0" />
            <blockpin signalname="XLXN_56" name="Q1" />
            <blockpin signalname="XLXN_55" name="Q2" />
            <blockpin signalname="RD" name="RD" />
            <blockpin signalname="RI" name="RI" />
            <blockpin signalname="S0" name="S0" />
            <blockpin signalname="S1" name="S1" />
            <blockpin signalname="VD" name="VD" />
            <blockpin signalname="VI" name="VI" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="816" y="1248" name="XLXI_3" orien="R0" />
        <instance x="816" y="896" name="XLXI_2" orien="R0" />
        <branch name="XLXN_52">
            <wire x2="752" y1="496" y2="640" x1="752" />
            <wire x2="816" y1="640" y2="640" x1="752" />
            <wire x2="2176" y1="496" y2="496" x1="752" />
            <wire x2="2176" y1="496" y2="928" x1="2176" />
            <wire x2="2176" y1="928" y2="928" x1="2112" />
        </branch>
        <branch name="XLXN_53">
            <wire x2="736" y1="480" y2="992" x1="736" />
            <wire x2="816" y1="992" y2="992" x1="736" />
            <wire x2="2192" y1="480" y2="480" x1="736" />
            <wire x2="2192" y1="480" y2="992" x1="2192" />
            <wire x2="2192" y1="992" y2="992" x1="2112" />
        </branch>
        <branch name="XLXN_56">
            <wire x2="1728" y1="992" y2="992" x1="1200" />
        </branch>
        <branch name="CLR">
            <wire x2="640" y1="480" y2="864" x1="640" />
            <wire x2="640" y1="864" y2="1216" x1="640" />
            <wire x2="816" y1="1216" y2="1216" x1="640" />
            <wire x2="640" y1="1216" y2="1568" x1="640" />
            <wire x2="816" y1="1568" y2="1568" x1="640" />
            <wire x2="816" y1="864" y2="864" x1="640" />
        </branch>
        <iomarker fontsize="28" x="640" y="480" name="CLR" orien="R270" />
        <iomarker fontsize="28" x="592" y="480" name="CLK" orien="R270" />
        <branch name="RD">
            <wire x2="2128" y1="1120" y2="1120" x1="2112" />
            <wire x2="2160" y1="1120" y2="1120" x1="2128" />
        </branch>
        <branch name="RI">
            <wire x2="2144" y1="1184" y2="1184" x1="2112" />
        </branch>
        <iomarker fontsize="28" x="2144" y="1184" name="RI" orien="R0" />
        <branch name="AD">
            <wire x2="2144" y1="1248" y2="1248" x1="2112" />
        </branch>
        <iomarker fontsize="28" x="2144" y="1248" name="AD" orien="R0" />
        <branch name="AI">
            <wire x2="2144" y1="1312" y2="1312" x1="2112" />
        </branch>
        <iomarker fontsize="28" x="2144" y="1312" name="AI" orien="R0" />
        <branch name="VD">
            <wire x2="2144" y1="1376" y2="1376" x1="2112" />
        </branch>
        <iomarker fontsize="28" x="2144" y="1376" name="VD" orien="R0" />
        <branch name="VI">
            <wire x2="2144" y1="1440" y2="1440" x1="2112" />
        </branch>
        <iomarker fontsize="28" x="2144" y="1440" name="VI" orien="R0" />
        <branch name="S1">
            <wire x2="1728" y1="1120" y2="1120" x1="1696" />
        </branch>
        <branch name="S0">
            <wire x2="1728" y1="1184" y2="1184" x1="1696" />
        </branch>
        <iomarker fontsize="28" x="1696" y="1184" name="S0" orien="R180" />
        <iomarker fontsize="28" x="1696" y="1120" name="S1" orien="R180" />
        <branch name="XLXN_55">
            <wire x2="1456" y1="640" y2="640" x1="1200" />
            <wire x2="1456" y1="640" y2="928" x1="1456" />
            <wire x2="1728" y1="928" y2="928" x1="1456" />
        </branch>
        <instance x="816" y="1600" name="XLXI_4" orien="R0" />
        <branch name="XLXN_54">
            <wire x2="720" y1="464" y2="1344" x1="720" />
            <wire x2="816" y1="1344" y2="1344" x1="720" />
            <wire x2="2208" y1="464" y2="464" x1="720" />
            <wire x2="2208" y1="464" y2="1056" x1="2208" />
            <wire x2="2208" y1="1056" y2="1056" x1="2112" />
        </branch>
        <branch name="XLXN_57">
            <wire x2="1456" y1="1344" y2="1344" x1="1200" />
            <wire x2="1456" y1="1056" y2="1344" x1="1456" />
            <wire x2="1728" y1="1056" y2="1056" x1="1456" />
        </branch>
        <branch name="CLK">
            <wire x2="592" y1="480" y2="768" x1="592" />
            <wire x2="592" y1="768" y2="1120" x1="592" />
            <wire x2="816" y1="1120" y2="1120" x1="592" />
            <wire x2="592" y1="1120" y2="1472" x1="592" />
            <wire x2="816" y1="1472" y2="1472" x1="592" />
            <wire x2="816" y1="768" y2="768" x1="592" />
        </branch>
        <iomarker fontsize="28" x="2160" y="1120" name="RD" orien="R0" />
        <instance x="1728" y="1472" name="XLXI_5" orien="R0">
        </instance>
    </sheet>
</drawing>