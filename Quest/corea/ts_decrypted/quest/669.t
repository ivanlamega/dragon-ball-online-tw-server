CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 669;
	title = 66902;

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
				conv = 66909;
				ctype = 1;
				idx = 4141101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 66908;
				gtype = 1;
				area = 66901;
				goal = 66904;
				grade = 132203;
				rwd = 100;
				sort = 66905;
				stype = 2;
				taid = 1;
				title = 66902;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 66907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 4141101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 30;
				minlvl = 22;
			}
			CDboTSCheckClrQst
			{
				and = "668;";
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
			cont = 66908;
			gtype = 1;
			oklnk = 2;
			area = 66901;
			goal = 66904;
			sort = 66905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 66902;
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
			desc = 66914;
			nextlnk = 254;
			rwdtbl = 66901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4151106;
			}
		}
	}
}

