CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 238;
	title = 23802;

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
				cont = 23808;
				gtype = 1;
				area = 23801;
				goal = 23804;
				grade = 132203;
				rwd = 100;
				sort = 23805;
				stype = 2;
				taid = 1;
				title = 23802;
			}
			CDboTSActNPCConv
			{
				conv = 23809;
				ctype = 1;
				idx = 3142210;
				taid = 2;
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
			cont = 23808;
			gtype = 1;
			oklnk = 2;
			area = 23801;
			goal = 23804;
			sort = 23805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 23802;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 23814;
			nextlnk = 254;
			rwdtbl = 23801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4651102;
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
		CDboTSContStart
		{
			cid = 0;
			stdiag = 23807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 3142210;
			}
			CDboTSCheckLvl
			{
				maxlvl = 15;
				minlvl = 7;
			}
			CDboTSCheckClrQst
			{
				and = "225;237;";
			}
		}
	}
}

