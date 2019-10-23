CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 509;
	title = 50902;

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
				conv = 50909;
				ctype = 1;
				idx = 3171101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 50908;
				gtype = 0;
				area = 50901;
				goal = 50904;
				grade = 132203;
				rwd = 100;
				sort = 50905;
				stype = 2;
				taid = 1;
				title = 50902;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 50907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3171101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 23;
				minlvl = 15;
			}
			CDboTSCheckClrQst
			{
				and = "504;";
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 50908;
			gtype = 0;
			oklnk = 2;
			area = 50901;
			goal = 50904;
			sort = 50905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 50902;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 50914;
			nextlnk = 254;
			rwdtbl = 50901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4141108;
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

