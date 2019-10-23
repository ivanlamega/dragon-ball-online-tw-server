CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6019;
	title = 601902;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 601909;
				ctype = 1;
				idx = 3221201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 601908;
				gtype = 1;
				area = 601901;
				goal = 601904;
				grade = -1;
				rwd = 100;
				sort = 601905;
				stype = 8;
				taid = 1;
				title = 601902;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 601907;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 3221201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6018;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;0;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 601908;
			gtype = 1;
			oklnk = 2;
			area = 601901;
			goal = 601904;
			sort = 601905;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 601902;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 601914;
			nextlnk = 253;
			rwdtbl = 601901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3181301;
			}
		}
	}
}

