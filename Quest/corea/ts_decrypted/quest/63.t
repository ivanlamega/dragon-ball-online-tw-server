CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 63;
	title = 6302;

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
				conv = 6309;
				ctype = 1;
				idx = 3331201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 6308;
				gtype = 0;
				area = 6301;
				goal = 6304;
				grade = 132203;
				rwd = 100;
				sort = 6305;
				stype = 1;
				taid = 1;
				title = 6302;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 6307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 2;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 3331101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 18;
				minlvl = 10;
			}
			CDboTSCheckClrQst
			{
				and = "60;";
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
			cont = 6308;
			gtype = 0;
			oklnk = 2;
			area = 6301;
			goal = 6304;
			sort = 6305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 6302;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 6314;
			nextlnk = 254;
			rwdtbl = 6301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4181101;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
	}
}

