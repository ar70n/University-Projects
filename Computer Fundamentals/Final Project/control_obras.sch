<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="Q2" />
        <signal name="Q1" />
        <signal name="Q0" />
        <signal name="S1" />
        <signal name="S0" />
        <signal name="XLXN_7" />
        <signal name="XLXN_8" />
        <signal name="XLXN_9" />
        <signal name="D2" />
        <signal name="XLXN_11" />
        <signal name="XLXN_12" />
        <signal name="D1" />
        <signal name="D0" />
        <signal name="XLXN_16" />
        <signal name="XLXN_15" />
        <signal name="XLXN_14" />
        <signal name="RD" />
        <signal name="RI" />
        <signal name="AD" />
        <signal name="AI" />
        <signal name="VD" />
        <signal name="XLXN_23" />
        <signal name="XLXN_24" />
        <signal name="VI" />
        <signal name="XLXN_36" />
        <signal name="XLXN_37" />
        <signal name="XLXN_93" />
        <signal name="XLXN_94" />
        <signal name="XLXN_95" />
        <port polarity="Input" name="Q2" />
        <port polarity="Input" name="Q1" />
        <port polarity="Input" name="Q0" />
        <port polarity="Input" name="S1" />
        <port polarity="Input" name="S0" />
        <port polarity="Output" name="D2" />
        <port polarity="Output" name="D1" />
        <port polarity="Output" name="D0" />
        <port polarity="Output" name="RD" />
        <port polarity="Output" name="RI" />
        <port polarity="Output" name="AD" />
        <port polarity="Output" name="AI" />
        <port polarity="Output" name="VD" />
        <port polarity="Output" name="VI" />
        <blockdef name="or3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="72" y1="-128" y2="-128" x1="0" />
            <line x2="48" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <arc ex="192" ey="-128" sx="112" sy="-80" r="88" cx="116" cy="-168" />
            <arc ex="48" ey="-176" sx="48" sy="-80" r="56" cx="16" cy="-128" />
            <line x2="48" y1="-64" y2="-80" x1="48" />
            <line x2="48" y1="-192" y2="-176" x1="48" />
            <line x2="48" y1="-80" y2="-80" x1="112" />
            <arc ex="112" ey="-176" sx="192" sy="-128" r="88" cx="116" cy="-88" />
            <line x2="48" y1="-176" y2="-176" x1="112" />
        </blockdef>
        <blockdef name="and2b1">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-48" y2="-144" x1="64" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
        </blockdef>
        <blockdef name="and3b1">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
        </blockdef>
        <blockdef name="or2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="192" ey="-96" sx="112" sy="-48" r="88" cx="116" cy="-136" />
            <arc ex="48" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <line x2="48" y1="-144" y2="-144" x1="112" />
            <arc ex="112" ey="-144" sx="192" sy="-96" r="88" cx="116" cy="-56" />
            <line x2="48" y1="-48" y2="-48" x1="112" />
        </blockdef>
        <blockdef name="and3b2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="40" y1="-128" y2="-128" x1="0" />
            <circle r="12" cx="52" cy="-128" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
        </blockdef>
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <blockdef name="and3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
        </blockdef>
        <blockdef name="and2b2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="40" y1="-64" y2="-64" x1="0" />
            <circle r="12" cx="52" cy="-64" />
            <line x2="40" y1="-128" y2="-128" x1="0" />
            <circle r="12" cx="52" cy="-128" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
        </blockdef>
        <blockdef name="buf">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="0" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="-64" x1="128" />
            <line x2="64" y1="-64" y2="0" x1="64" />
        </blockdef>
        <block symbolname="or3" name="XLXI_2">
            <blockpin signalname="XLXN_9" name="I0" />
            <blockpin signalname="XLXN_8" name="I1" />
            <blockpin signalname="XLXN_7" name="I2" />
            <blockpin signalname="D2" name="O" />
        </block>
        <block symbolname="and2b1" name="XLXI_3">
            <blockpin signalname="Q0" name="I0" />
            <blockpin signalname="Q2" name="I1" />
            <blockpin signalname="XLXN_7" name="O" />
        </block>
        <block symbolname="and2b1" name="XLXI_4">
            <blockpin signalname="Q1" name="I0" />
            <blockpin signalname="Q2" name="I1" />
            <blockpin signalname="XLXN_8" name="O" />
        </block>
        <block symbolname="and3b1" name="XLXI_5">
            <blockpin signalname="Q2" name="I0" />
            <blockpin signalname="Q0" name="I1" />
            <blockpin signalname="Q1" name="I2" />
            <blockpin signalname="XLXN_9" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_6">
            <blockpin signalname="XLXN_12" name="I0" />
            <blockpin signalname="XLXN_11" name="I1" />
            <blockpin signalname="D1" name="O" />
        </block>
        <block symbolname="and2b1" name="XLXI_7">
            <blockpin signalname="Q1" name="I0" />
            <blockpin signalname="Q0" name="I1" />
            <blockpin signalname="XLXN_11" name="O" />
        </block>
        <block symbolname="and2b1" name="XLXI_8">
            <blockpin signalname="Q0" name="I0" />
            <blockpin signalname="Q1" name="I1" />
            <blockpin signalname="XLXN_12" name="O" />
        </block>
        <block symbolname="and3b1" name="XLXI_12">
            <blockpin signalname="Q0" name="I0" />
            <blockpin signalname="Q2" name="I1" />
            <blockpin signalname="S0" name="I2" />
            <blockpin signalname="XLXN_16" name="O" />
        </block>
        <block symbolname="and3b2" name="XLXI_11">
            <blockpin signalname="Q0" name="I0" />
            <blockpin signalname="Q2" name="I1" />
            <blockpin signalname="S1" name="I2" />
            <blockpin signalname="XLXN_15" name="O" />
        </block>
        <block symbolname="and2b1" name="XLXI_10">
            <blockpin signalname="Q0" name="I0" />
            <blockpin signalname="Q1" name="I1" />
            <blockpin signalname="XLXN_14" name="O" />
        </block>
        <block symbolname="or3" name="XLXI_9">
            <blockpin signalname="XLXN_16" name="I0" />
            <blockpin signalname="XLXN_15" name="I1" />
            <blockpin signalname="XLXN_14" name="I2" />
            <blockpin signalname="D0" name="O" />
        </block>
        <block symbolname="buf" name="XLXI_22">
            <blockpin signalname="Q2" name="I" />
            <blockpin signalname="RD" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_14">
            <blockpin signalname="Q2" name="I" />
            <blockpin signalname="RI" name="O" />
        </block>
        <block symbolname="and3b1" name="XLXI_13">
            <blockpin signalname="Q2" name="I0" />
            <blockpin signalname="Q1" name="I1" />
            <blockpin signalname="Q0" name="I2" />
            <blockpin signalname="AD" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_15">
            <blockpin signalname="Q2" name="I0" />
            <blockpin signalname="Q0" name="I1" />
            <blockpin signalname="Q1" name="I2" />
            <blockpin signalname="AI" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_16">
            <blockpin signalname="XLXN_24" name="I0" />
            <blockpin signalname="XLXN_23" name="I1" />
            <blockpin signalname="VD" name="O" />
        </block>
        <block symbolname="and2b2" name="XLXI_17">
            <blockpin signalname="Q0" name="I0" />
            <blockpin signalname="Q2" name="I1" />
            <blockpin signalname="XLXN_23" name="O" />
        </block>
        <block symbolname="and2b2" name="XLXI_18">
            <blockpin signalname="Q1" name="I0" />
            <blockpin signalname="Q2" name="I1" />
            <blockpin signalname="XLXN_24" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_19">
            <blockpin signalname="XLXN_37" name="I0" />
            <blockpin signalname="XLXN_36" name="I1" />
            <blockpin signalname="VI" name="O" />
        </block>
        <block symbolname="and2b1" name="XLXI_20">
            <blockpin signalname="Q0" name="I0" />
            <blockpin signalname="Q2" name="I1" />
            <blockpin signalname="XLXN_36" name="O" />
        </block>
        <block symbolname="and2b1" name="XLXI_21">
            <blockpin signalname="Q1" name="I0" />
            <blockpin signalname="Q2" name="I1" />
            <blockpin signalname="XLXN_37" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <iomarker fontsize="28" x="416" y="176" name="Q2" orien="R270" />
        <iomarker fontsize="28" x="448" y="176" name="Q1" orien="R270" />
        <iomarker fontsize="28" x="480" y="176" name="Q0" orien="R270" />
        <iomarker fontsize="28" x="512" y="176" name="S1" orien="R270" />
        <iomarker fontsize="28" x="544" y="176" name="S0" orien="R270" />
        <instance x="784" y="688" name="XLXI_5" orien="R0" />
        <instance x="784" y="336" name="XLXI_3" orien="R0" />
        <instance x="784" y="496" name="XLXI_4" orien="R0" />
        <branch name="XLXN_7">
            <wire x2="1328" y1="240" y2="240" x1="1040" />
            <wire x2="1328" y1="240" y2="336" x1="1328" />
        </branch>
        <branch name="XLXN_8">
            <wire x2="1328" y1="400" y2="400" x1="1040" />
        </branch>
        <branch name="XLXN_9">
            <wire x2="1328" y1="560" y2="560" x1="1040" />
            <wire x2="1328" y1="464" y2="560" x1="1328" />
        </branch>
        <branch name="D2">
            <wire x2="1632" y1="400" y2="400" x1="1584" />
        </branch>
        <iomarker fontsize="28" x="1632" y="400" name="D2" orien="R0" />
        <instance x="1328" y="528" name="XLXI_2" orien="R0" />
        <branch name="Q0">
            <wire x2="480" y1="176" y2="272" x1="480" />
            <wire x2="784" y1="272" y2="272" x1="480" />
            <wire x2="480" y1="272" y2="560" x1="480" />
            <wire x2="784" y1="560" y2="560" x1="480" />
            <wire x2="480" y1="560" y2="672" x1="480" />
            <wire x2="768" y1="672" y2="672" x1="480" />
            <wire x2="480" y1="672" y2="896" x1="480" />
            <wire x2="768" y1="896" y2="896" x1="480" />
            <wire x2="480" y1="896" y2="928" x1="480" />
            <wire x2="480" y1="928" y2="1552" x1="480" />
            <wire x2="480" y1="1552" y2="1744" x1="480" />
            <wire x2="480" y1="1744" y2="1904" x1="480" />
            <wire x2="800" y1="1904" y2="1904" x1="480" />
            <wire x2="800" y1="1744" y2="1744" x1="480" />
            <wire x2="784" y1="1552" y2="1552" x1="480" />
            <wire x2="1936" y1="928" y2="928" x1="480" />
            <wire x2="2080" y1="928" y2="928" x1="1936" />
            <wire x2="1936" y1="928" y2="1200" x1="1936" />
            <wire x2="2064" y1="1200" y2="1200" x1="1936" />
            <wire x2="1936" y1="1200" y2="1392" x1="1936" />
            <wire x2="2064" y1="1392" y2="1392" x1="1936" />
            <wire x2="1936" y1="1392" y2="1696" x1="1936" />
            <wire x2="2064" y1="1696" y2="1696" x1="1936" />
        </branch>
        <branch name="XLXN_11">
            <wire x2="1168" y1="704" y2="704" x1="1024" />
            <wire x2="1168" y1="704" y2="752" x1="1168" />
            <wire x2="1328" y1="752" y2="752" x1="1168" />
        </branch>
        <branch name="XLXN_12">
            <wire x2="1168" y1="864" y2="864" x1="1024" />
            <wire x2="1168" y1="816" y2="864" x1="1168" />
            <wire x2="1328" y1="816" y2="816" x1="1168" />
        </branch>
        <branch name="D1">
            <wire x2="1616" y1="784" y2="784" x1="1584" />
        </branch>
        <instance x="1328" y="880" name="XLXI_6" orien="R0" />
        <instance x="768" y="800" name="XLXI_7" orien="R0" />
        <instance x="768" y="960" name="XLXI_8" orien="R0" />
        <iomarker fontsize="28" x="1616" y="784" name="D1" orien="R0" />
        <branch name="S0">
            <wire x2="544" y1="176" y2="1776" x1="544" />
            <wire x2="800" y1="1776" y2="1776" x1="544" />
        </branch>
        <branch name="S1">
            <wire x2="512" y1="176" y2="1616" x1="512" />
            <wire x2="800" y1="1616" y2="1616" x1="512" />
        </branch>
        <iomarker fontsize="28" x="1632" y="1680" name="D0" orien="R0" />
        <branch name="D0">
            <wire x2="1632" y1="1680" y2="1680" x1="1600" />
        </branch>
        <branch name="XLXN_16">
            <wire x2="1344" y1="1840" y2="1840" x1="1056" />
            <wire x2="1344" y1="1744" y2="1840" x1="1344" />
        </branch>
        <branch name="XLXN_15">
            <wire x2="1344" y1="1680" y2="1680" x1="1056" />
        </branch>
        <branch name="XLXN_14">
            <wire x2="1344" y1="1520" y2="1520" x1="1040" />
            <wire x2="1344" y1="1520" y2="1616" x1="1344" />
        </branch>
        <instance x="800" y="1968" name="XLXI_12" orien="R0" />
        <instance x="800" y="1808" name="XLXI_11" orien="R0" />
        <instance x="1344" y="1808" name="XLXI_9" orien="R0" />
        <branch name="Q2">
            <wire x2="416" y1="176" y2="208" x1="416" />
            <wire x2="784" y1="208" y2="208" x1="416" />
            <wire x2="416" y1="208" y2="368" x1="416" />
            <wire x2="784" y1="368" y2="368" x1="416" />
            <wire x2="416" y1="368" y2="624" x1="416" />
            <wire x2="784" y1="624" y2="624" x1="416" />
            <wire x2="416" y1="624" y2="1040" x1="416" />
            <wire x2="416" y1="1040" y2="1680" x1="416" />
            <wire x2="800" y1="1680" y2="1680" x1="416" />
            <wire x2="416" y1="1680" y2="1840" x1="416" />
            <wire x2="800" y1="1840" y2="1840" x1="416" />
            <wire x2="1744" y1="1040" y2="1040" x1="416" />
            <wire x2="1744" y1="1040" y2="1056" x1="1744" />
            <wire x2="1872" y1="1056" y2="1056" x1="1744" />
            <wire x2="2080" y1="1056" y2="1056" x1="1872" />
            <wire x2="1872" y1="1056" y2="1264" x1="1872" />
            <wire x2="2064" y1="1264" y2="1264" x1="1872" />
            <wire x2="1872" y1="1264" y2="1328" x1="1872" />
            <wire x2="2064" y1="1328" y2="1328" x1="1872" />
            <wire x2="1872" y1="1328" y2="1488" x1="1872" />
            <wire x2="2064" y1="1488" y2="1488" x1="1872" />
            <wire x2="1872" y1="1488" y2="1632" x1="1872" />
            <wire x2="2064" y1="1632" y2="1632" x1="1872" />
            <wire x2="1872" y1="1632" y2="1792" x1="1872" />
            <wire x2="2064" y1="1792" y2="1792" x1="1872" />
            <wire x2="2064" y1="784" y2="784" x1="1744" />
            <wire x2="1744" y1="784" y2="864" x1="1744" />
            <wire x2="2064" y1="864" y2="864" x1="1744" />
            <wire x2="1744" y1="864" y2="1040" x1="1744" />
        </branch>
        <instance x="784" y="1616" name="XLXI_10" orien="R0" />
        <branch name="RD">
            <wire x2="2320" y1="784" y2="784" x1="2288" />
        </branch>
        <instance x="2064" y="816" name="XLXI_22" orien="R0" />
        <iomarker fontsize="28" x="2320" y="784" name="RD" orien="R0" />
        <branch name="RI">
            <wire x2="2320" y1="864" y2="864" x1="2288" />
        </branch>
        <instance x="2064" y="896" name="XLXI_14" orien="R0" />
        <iomarker fontsize="28" x="2320" y="864" name="RI" orien="R0" />
        <branch name="AD">
            <wire x2="2368" y1="992" y2="992" x1="2336" />
        </branch>
        <iomarker fontsize="28" x="2368" y="992" name="AD" orien="R0" />
        <instance x="2080" y="1120" name="XLXI_13" orien="R0" />
        <branch name="AI">
            <wire x2="2352" y1="1200" y2="1200" x1="2320" />
        </branch>
        <instance x="2064" y="1328" name="XLXI_15" orien="R0" />
        <iomarker fontsize="28" x="2352" y="1200" name="AI" orien="R0" />
        <branch name="VD">
            <wire x2="2672" y1="1440" y2="1440" x1="2640" />
        </branch>
        <branch name="XLXN_23">
            <wire x2="2352" y1="1360" y2="1360" x1="2320" />
            <wire x2="2352" y1="1360" y2="1408" x1="2352" />
            <wire x2="2384" y1="1408" y2="1408" x1="2352" />
        </branch>
        <branch name="XLXN_24">
            <wire x2="2352" y1="1520" y2="1520" x1="2320" />
            <wire x2="2352" y1="1472" y2="1520" x1="2352" />
            <wire x2="2384" y1="1472" y2="1472" x1="2352" />
        </branch>
        <instance x="2384" y="1536" name="XLXI_16" orien="R0" />
        <instance x="2064" y="1456" name="XLXI_17" orien="R0" />
        <instance x="2064" y="1616" name="XLXI_18" orien="R0" />
        <iomarker fontsize="28" x="2672" y="1440" name="VD" orien="R0" />
        <branch name="VI">
            <wire x2="2656" y1="1712" y2="1712" x1="2624" />
        </branch>
        <branch name="XLXN_36">
            <wire x2="2352" y1="1664" y2="1664" x1="2320" />
            <wire x2="2352" y1="1664" y2="1680" x1="2352" />
            <wire x2="2368" y1="1680" y2="1680" x1="2352" />
        </branch>
        <branch name="XLXN_37">
            <wire x2="2336" y1="1824" y2="1824" x1="2320" />
            <wire x2="2336" y1="1744" y2="1824" x1="2336" />
            <wire x2="2368" y1="1744" y2="1744" x1="2336" />
        </branch>
        <instance x="2368" y="1808" name="XLXI_19" orien="R0" />
        <instance x="2064" y="1920" name="XLXI_21" orien="R0" />
        <iomarker fontsize="28" x="2656" y="1712" name="VI" orien="R0" />
        <instance x="2064" y="1760" name="XLXI_20" orien="R0" />
        <branch name="Q1">
            <wire x2="448" y1="176" y2="432" x1="448" />
            <wire x2="784" y1="432" y2="432" x1="448" />
            <wire x2="448" y1="432" y2="496" x1="448" />
            <wire x2="784" y1="496" y2="496" x1="448" />
            <wire x2="448" y1="496" y2="736" x1="448" />
            <wire x2="768" y1="736" y2="736" x1="448" />
            <wire x2="448" y1="736" y2="832" x1="448" />
            <wire x2="768" y1="832" y2="832" x1="448" />
            <wire x2="448" y1="832" y2="992" x1="448" />
            <wire x2="448" y1="992" y2="1488" x1="448" />
            <wire x2="784" y1="1488" y2="1488" x1="448" />
            <wire x2="1968" y1="992" y2="992" x1="448" />
            <wire x2="2080" y1="992" y2="992" x1="1968" />
            <wire x2="1968" y1="992" y2="1136" x1="1968" />
            <wire x2="2064" y1="1136" y2="1136" x1="1968" />
            <wire x2="1968" y1="1136" y2="1552" x1="1968" />
            <wire x2="2064" y1="1552" y2="1552" x1="1968" />
            <wire x2="1968" y1="1552" y2="1856" x1="1968" />
            <wire x2="2064" y1="1856" y2="1856" x1="1968" />
        </branch>
    </sheet>
</drawing>