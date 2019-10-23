CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1610;
	title = 161002;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 161009;
				ctype = 1;
				idx = 5061101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 161008;
				gtype = 0;
				area = 161001;
				goal = 161004;
				grade = 132203;
				rwd = 100;
				sort = 161005;
				stype = 2;
				taid = 1;
				title = 161002;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 161014;
			nextlnk = 254;
			rwdtbl = 161001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4071117;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 161008;
			gtype = 0;
			oklnk = 2;
			area = 161001;
			goal = 161004;
			sort = 161005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 161002;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 161007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5061111;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
			CDboTSCheckClrQst
			{
				and = "1599;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
	}
}

