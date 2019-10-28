CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1377;
	title = 137702;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActItem
			{
				iidx0 = 99048;
				stype0 = 1;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 137707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckLvl
			{
				maxlvl = 54;
				minlvl = 46;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 137708;
				gtype = 1;
				area = 137701;
				goal = 137704;
				grade = 132203;
				rwd = 100;
				sort = 137705;
				stype = 1;
				taid = 1;
				title = 137702;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 137714;
			nextlnk = 101;
			rwdtbl = 137701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickObject
			{
				objidx = "696;";
				widx = 1;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 137708;
			gtype = 1;
			oklnk = 2;
			area = 137701;
			goal = 137704;
			sort = 137705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 137702;
		}
	}
}

