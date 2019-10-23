CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 112;
	title = 11202;

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
				conv = 11209;
				ctype = 1;
				idx = 3183102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 11208;
				gtype = 1;
				area = 11201;
				goal = 11204;
				grade = 132203;
				rwd = 100;
				sort = 11205;
				stype = 1;
				taid = 1;
				title = 11202;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 11207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3183102;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckLvl
			{
				maxlvl = 24;
				minlvl = 16;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 11208;
			gtype = 1;
			oklnk = 2;
			area = 11201;
			goal = 11204;
			sort = 11205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 11202;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 11214;
			nextlnk = 254;
			rwdtbl = 11201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7091101;
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
	}
}

