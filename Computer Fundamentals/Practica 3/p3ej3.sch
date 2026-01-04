<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="artix7" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_9" />
        <signal name="XLXN_10" />
        <signal name="XLXN_11" />
        <signal name="XLXN_12" />
        <signal name="XLXN_15" />
        <signal name="XLXN_19" />
        <signal name="XLXN_22" />
        <signal name="XLXN_26" />
        <signal name="XLXN_27" />
        <signal name="XLXN_30" />
        <signal name="XLXN_34" />
        <signal name="XLXN_39" />
        <signal name="XLXN_40" />
        <signal name="XLXN_41" />
        <signal name="XLXN_42" />
        <signal name="XLXN_43" />
        <signal name="XLXN_45" />
        <signal name="XLXN_46" />
        <signal name="XLXN_47" />
        <signal name="SIG_DIV" />
        <signal name="INIT" />
        <signal name="CLK" />
        <port polarity="Output" name="SIG_DIV" />
        <port polarity="Input" name="INIT" />
        <port polarity="Input" name="CLK" />
        <blockdef name="cd4cle">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="320" y1="-192" y2="-192" x1="384" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="64" y1="-576" y2="-576" x1="0" />
            <line x2="64" y1="-512" y2="-512" x1="0" />
            <line x2="64" y1="-448" y2="-448" x1="0" />
            <line x2="64" y1="-384" y2="-384" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="320" y1="-576" y2="-576" x1="384" />
            <line x2="320" y1="-512" y2="-512" x1="384" />
            <line x2="320" y1="-448" y2="-448" x1="384" />
            <line x2="320" y1="-384" y2="-384" x1="384" />
            <line x2="320" y1="-128" y2="-128" x1="384" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <rect width="256" x="64" y="-640" height="576" />
        </blockdef>
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-64" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-64" y2="-64" x1="96" />
        </blockdef>
        <blockdef name="gnd">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-96" x1="64" />
            <line x2="52" y1="-48" y2="-48" x1="76" />
            <line x2="60" y1="-32" y2="-32" x1="68" />
            <line x2="40" y1="-64" y2="-64" x1="88" />
            <line x2="64" y1="-64" y2="-80" x1="64" />
            <line x2="64" y1="-128" y2="-96" x1="64" />
        </blockdef>
        <blockdef name="and2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
        </blockdef>
        <block symbolname="cd4cle" name="XLXI_1">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_15" name="CE" />
            <blockpin signalname="INIT" name="CLR" />
            <blockpin signalname="XLXN_19" name="D0" />
            <blockpin signalname="XLXN_19" name="D1" />
            <blockpin signalname="XLXN_19" name="D2" />
            <blockpin signalname="XLXN_19" name="D3" />
            <blockpin signalname="XLXN_10" name="L" />
            <blockpin name="CEO" />
            <blockpin signalname="XLXN_9" name="Q0" />
            <blockpin signalname="XLXN_10" name="Q1" />
            <blockpin signalname="XLXN_11" name="Q2" />
            <blockpin signalname="XLXN_12" name="Q3" />
            <blockpin name="TC" />
        </block>
        <block symbolname="cd4cle" name="XLXI_2">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_10" name="CE" />
            <blockpin signalname="INIT" name="CLR" />
            <blockpin signalname="XLXN_22" name="D0" />
            <blockpin signalname="XLXN_22" name="D1" />
            <blockpin signalname="XLXN_22" name="D2" />
            <blockpin signalname="XLXN_22" name="D3" />
            <blockpin signalname="SIG_DIV" name="L" />
            <blockpin name="CEO" />
            <blockpin signalname="XLXN_46" name="Q0" />
            <blockpin name="Q1" />
            <blockpin signalname="XLXN_47" name="Q2" />
            <blockpin name="Q3" />
            <blockpin name="TC" />
        </block>
        <block symbolname="vcc" name="XLXI_4">
            <blockpin signalname="XLXN_15" name="P" />
        </block>
        <block symbolname="gnd" name="XLXI_5">
            <blockpin signalname="XLXN_19" name="G" />
        </block>
        <block symbolname="gnd" name="XLXI_6">
            <blockpin signalname="XLXN_22" name="G" />
        </block>
        <block symbolname="and2" name="XLXI_12">
            <blockpin signalname="XLXN_47" name="I0" />
            <blockpin signalname="XLXN_46" name="I1" />
            <blockpin signalname="SIG_DIV" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1952" y="1920" name="XLXI_2" orien="R0" />
        <branch name="XLXN_9">
            <wire x2="1520" y1="1312" y2="1312" x1="1456" />
        </branch>
        <branch name="XLXN_10">
            <wire x2="1072" y1="1632" y2="1632" x1="16" />
            <wire x2="16" y1="1632" y2="2656" x1="16" />
            <wire x2="1728" y1="2656" y2="2656" x1="16" />
            <wire x2="1520" y1="1376" y2="1376" x1="1456" />
            <wire x2="1728" y1="1376" y2="1376" x1="1520" />
            <wire x2="1728" y1="1376" y2="1728" x1="1728" />
            <wire x2="1952" y1="1728" y2="1728" x1="1728" />
            <wire x2="1728" y1="1728" y2="2656" x1="1728" />
        </branch>
        <branch name="XLXN_11">
            <wire x2="1520" y1="1440" y2="1440" x1="1456" />
        </branch>
        <branch name="XLXN_12">
            <wire x2="1520" y1="1504" y2="1504" x1="1456" />
        </branch>
        <instance x="608" y="1760" name="XLXI_4" orien="R0" />
        <branch name="XLXN_15">
            <wire x2="672" y1="1760" y2="1824" x1="672" />
            <wire x2="768" y1="1824" y2="1824" x1="672" />
            <wire x2="768" y1="1696" y2="1824" x1="768" />
            <wire x2="1072" y1="1696" y2="1696" x1="768" />
        </branch>
        <instance x="640" y="1488" name="XLXI_5" orien="R0" />
        <instance x="1664" y="1216" name="XLXI_6" orien="R0" />
        <branch name="XLXN_22">
            <wire x2="1728" y1="1008" y2="1088" x1="1728" />
            <wire x2="1840" y1="1008" y2="1008" x1="1728" />
            <wire x2="1840" y1="1008" y2="1344" x1="1840" />
            <wire x2="1904" y1="1344" y2="1344" x1="1840" />
            <wire x2="1952" y1="1344" y2="1344" x1="1904" />
            <wire x2="1904" y1="1344" y2="1408" x1="1904" />
            <wire x2="1952" y1="1408" y2="1408" x1="1904" />
            <wire x2="1904" y1="1408" y2="1472" x1="1904" />
            <wire x2="1952" y1="1472" y2="1472" x1="1904" />
            <wire x2="1904" y1="1472" y2="1536" x1="1904" />
            <wire x2="1952" y1="1536" y2="1536" x1="1904" />
        </branch>
        <instance x="1072" y="1888" name="XLXI_1" orien="R0" />
        <branch name="XLXN_19">
            <wire x2="704" y1="1296" y2="1360" x1="704" />
            <wire x2="800" y1="1296" y2="1296" x1="704" />
            <wire x2="800" y1="1296" y2="1312" x1="800" />
            <wire x2="1072" y1="1312" y2="1312" x1="800" />
            <wire x2="800" y1="1312" y2="1440" x1="800" />
            <wire x2="1072" y1="1440" y2="1440" x1="800" />
            <wire x2="800" y1="1440" y2="1504" x1="800" />
            <wire x2="1072" y1="1504" y2="1504" x1="800" />
            <wire x2="784" y1="1312" y2="1376" x1="784" />
            <wire x2="1072" y1="1376" y2="1376" x1="784" />
            <wire x2="800" y1="1312" y2="1312" x1="784" />
        </branch>
        <instance x="2416" y="1504" name="XLXI_12" orien="R0" />
        <branch name="XLXN_46">
            <wire x2="2368" y1="1344" y2="1344" x1="2336" />
            <wire x2="2368" y1="1344" y2="1376" x1="2368" />
            <wire x2="2416" y1="1376" y2="1376" x1="2368" />
        </branch>
        <branch name="XLXN_47">
            <wire x2="2368" y1="1472" y2="1472" x1="2336" />
            <wire x2="2368" y1="1440" y2="1472" x1="2368" />
            <wire x2="2416" y1="1440" y2="1440" x1="2368" />
        </branch>
        <branch name="SIG_DIV">
            <wire x2="1952" y1="1664" y2="1664" x1="1872" />
            <wire x2="1872" y1="1664" y2="1952" x1="1872" />
            <wire x2="2752" y1="1952" y2="1952" x1="1872" />
            <wire x2="2752" y1="1408" y2="1408" x1="2672" />
            <wire x2="2752" y1="1408" y2="1952" x1="2752" />
            <wire x2="2944" y1="1408" y2="1408" x1="2752" />
        </branch>
        <branch name="INIT">
            <wire x2="976" y1="2000" y2="2000" x1="832" />
            <wire x2="1072" y1="2000" y2="2000" x1="976" />
            <wire x2="1952" y1="1888" y2="1888" x1="976" />
            <wire x2="976" y1="1888" y2="2000" x1="976" />
            <wire x2="1072" y1="1856" y2="2000" x1="1072" />
        </branch>
        <branch name="CLK">
            <wire x2="1072" y1="1760" y2="1760" x1="1056" />
            <wire x2="1056" y1="1760" y2="2192" x1="1056" />
            <wire x2="1168" y1="2192" y2="2192" x1="1056" />
            <wire x2="1552" y1="2192" y2="2192" x1="1168" />
            <wire x2="1056" y1="2192" y2="2304" x1="1056" />
            <wire x2="1552" y1="1792" y2="2192" x1="1552" />
            <wire x2="1952" y1="1792" y2="1792" x1="1552" />
        </branch>
        <iomarker fontsize="28" x="832" y="2000" name="INIT" orien="R180" />
        <iomarker fontsize="28" x="1056" y="2304" name="CLK" orien="R90" />
        <iomarker fontsize="28" x="2944" y="1408" name="SIG_DIV" orien="R0" />
    </sheet>
</drawing>