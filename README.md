### Bamboo is a fork of [PIVX](https://github.com/PIVX-Project/PIVX) that forked [Dash](https://github.com/dashpay/dash) that forked [Bitcoin](https://github.com/bitcoin/bitcoinp)


# Bamboo Core integration/staging repository


### Coin Specs
<table>
<tr><td>Block Time</td><td>120 Seconds</td></tr>
<tr><td>Difficulty Retargeting</td><td>Every Block</td></tr>
<tr><td>Max Coin Supply </td><td>21,000,000 BOO</td></tr>
<tr><td>MN Port</td><td>8000</td></tr>
<tr><td>RPC Port</td><td>8050</td></tr>
</table>


### Reward Distribution Per Block

<table>
<th colspan=4>PoW Phase</th>
<tr><th>Block Height</th><th>Reward Amount</th><th>Notes</th><th>Duration (Days)</th></tr>
<tr><td>0</td><td>0 BOO</td><td>Genesis Block</td><td>0 Days</td></tr>
<tr><td>1-5</td><td>2,010,000 BOO</td><td>Initial Premine</td><td>0 Days</td></tr>
<tr><td>6-200</td><td>0 BOO</td><td rowspan=1>Closed Mining</td><td>1 Days</td></tr>
<tr><th colspan=4>PoS / MN Phase</th></tr>
<tr><td>201-10079</td><td>1 BOO</td><td rowspan=1>Ramp Up</td><td>14 Days</td></tr>
<tr><td>10080-9980000</td><td>2 BOO</td><td rowspan=1>Stable</td><td>38 Years</td></tr>
</table>


### Masternode Rewards Per Block, 50000 BOO Collateral

<table>
<tr><th>Block Height</th><th>MN Reward Amount</th><th>PoS Reward Amount</th><th>Duration (Days)</th><th>Development Fee</th></tr>
<tr><td>201-31679</td><td>30%</td><td>70%</td><td>14 Days</td><td>0%</td></tr>
<tr><td>31680-74879 </td><td>35%</td><td>65%</td><td>60 Days</td><td>0%</td></tr>
<tr><td>74880-206279 </td><td>40%</td><td>60%</td><td>182.5 Days</td><td>0%</td></tr>
<tr><td>206280-9980000 </td><td>50%</td><td>50%</td><td>37.5 Years</td><td>0%</td></tr>
</table>

MN Port: 8000
RPC Port: 8050
Testnet: 8050
