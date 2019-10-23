CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 340;
	title = 34002;

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
				conv = 34009;
				ctype = 1;
				idx = 4511607;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 34008;
				gtype = 1;
				area = 34001;
				goal = 34004;
				grade = 132203;
				rwd = 100;
				sort = 34005;
				stype = 1;
				taid = 1;
				title = 34002;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 34007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4511607;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 13;
				minlvl = 5;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 34008;
			gtype = 1;
			oklnk = 2;
			area = 34001;
			goal = 34004;
			sort = 34005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 34002;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 34014;
			nextlnk = 254;
			rwdtbl = 34001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 8512133;
			}
		}
	}
}

