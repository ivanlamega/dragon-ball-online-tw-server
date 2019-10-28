CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 254;
	title = 25402;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 25408;
				gtype = 1;
				area = 25401;
				goal = 25404;
				grade = 132203;
				rwd = 100;
				sort = 25405;
				stype = 2;
				taid = 1;
				title = 25402;
			}
			CDboTSActNPCConv
			{
				conv = 25409;
				ctype = 1;
				idx = 4751201;
				taid = 2;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 25414;
			nextlnk = 254;
			rwdtbl = 25401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4751106;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 25407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 4751201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 18;
				minlvl = 10;
			}
			CDboTSCheckClrQst
			{
				and = "251;";
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 25408;
			gtype = 1;
			oklnk = 2;
			area = 25401;
			goal = 25404;
			sort = 25405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 25402;
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

