CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 89;
	title = 8902;

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
				conv = 8909;
				ctype = 1;
				idx = 3183104;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 8908;
				gtype = 0;
				area = 8901;
				goal = 8904;
				grade = 132203;
				rwd = 100;
				sort = 8905;
				stype = 1;
				taid = 1;
				title = 8902;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 8907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3183104;
			}
			CDboTSCheckPCCls
			{
				clsflg = 2;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckLvl
			{
				maxlvl = 21;
				minlvl = 13;
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
			cont = 8908;
			gtype = 0;
			oklnk = 2;
			area = 8901;
			goal = 8904;
			sort = 8905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 8902;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 8914;
			nextlnk = 254;
			rwdtbl = 8901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3221203;
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
	}
}

