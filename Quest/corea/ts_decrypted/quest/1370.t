CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1370;
	title = 137002;

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
				conv = 137009;
				ctype = 1;
				idx = 4111101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 137008;
				gtype = 0;
				area = 137001;
				goal = 137004;
				grade = 132203;
				rwd = 100;
				sort = 137005;
				stype = 1;
				taid = 1;
				title = 137002;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 137007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4111101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 54;
				minlvl = 46;
			}
			CDboTSCheckClrQst
			{
				and = "1368;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 137008;
			gtype = 0;
			oklnk = 2;
			area = 137001;
			goal = 137004;
			sort = 137005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 137002;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 137014;
			nextlnk = 254;
			rwdtbl = 137001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4372101;
			}
		}
	}
}

