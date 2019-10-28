CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 463;
	title = 46302;

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
				conv = 46309;
				ctype = 1;
				idx = 4151201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 46308;
				gtype = 0;
				area = 46301;
				goal = 46304;
				grade = 132203;
				rwd = 100;
				sort = 46305;
				stype = 2;
				taid = 1;
				title = 46302;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 46314;
			nextlnk = 254;
			rwdtbl = 46301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4372207;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 46307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 19;
				minlvl = 11;
			}
			CDboTSCheckClrQst
			{
				and = "454;";
			}
			CDboTSClickNPC
			{
				npcidx = 4151201;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
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
			cont = 46308;
			gtype = 0;
			oklnk = 2;
			area = 46301;
			goal = 46304;
			sort = 46305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 46302;
		}
	}
}

