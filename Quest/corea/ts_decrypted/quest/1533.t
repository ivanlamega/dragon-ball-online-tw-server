CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1533;
	title = 153302;

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
				conv = 153309;
				ctype = 1;
				idx = 3142116;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 153308;
				gtype = 0;
				area = 153301;
				goal = 153304;
				grade = 132203;
				rwd = 100;
				sort = 153305;
				stype = 2;
				taid = 1;
				title = 153302;
			}
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 153314;
			nextlnk = 254;
			rwdtbl = 153301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3331205;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 153308;
			gtype = 0;
			oklnk = 2;
			area = 153301;
			goal = 153304;
			sort = 153305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 153302;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 153307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3142116;
			}
			CDboTSCheckLvl
			{
				maxlvl = 56;
				minlvl = 48;
			}
			CDboTSCheckClrQst
			{
				and = "1518;";
			}
		}
	}
}

